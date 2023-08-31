#include <stdexcept>

#include "Model.h"

// public

bool s21::Model::InsertSymbol(char symbol) { return PreParcer_(symbol); }

calc_res s21::Model::GetCalcResult(double x_value) {
  std::string t_str = CreateRPN_();
  double result = 0;
  calc_res res;
  res.calc_succes_ = false;
  res.result_ = 0;
  if (t_str != "Error") {
    if (ProcessingRpn_(t_str, x_value, result) == 0) {
      res.calc_succes_ = true;
      res.result_ = result;
    }
  }
  return res;
}

std::string &s21::Model::GetString() { return i_str_; }

void s21::Model::ClearStr() { i_str_.clear(); }

std::string s21::Model::GetRPN() { return CreateRPN_(); }

bool s21::Model::PartClear() {
  bool empty_str = i_str_.empty();
  bool done = false;
  if (!empty_str) {
    done = true;
    if (i_str_[i_str_.size() - 1] == '(') {
      bool stop = false;
      while (!stop) {
        i_str_.erase(i_str_.size() - 1);
        size_t i = i_str_.size() - 1;
        stop = (i_str_.empty() || i_str_[i] == '(' || i_str_[i] == '*' ||
                i_str_[i] == '/' || i_str_[i] == '-' || i_str_[i] == '+' ||
                i_str_[i] == '^');
      }
    } else {
      i_str_.erase(i_str_.size() - 1);
    }
  }
  return done;
}

// private

int s21::Model::StatusSymb_(char symbol) {
  int status = FORBIDDEN;
  std::string pattern = "0123456789.+-*/%^()ctsaliogqrnxE";
  size_t found = pattern.find(symbol);
  if (found <= 9) {
    status = DIGIT;
  } else if (found == 10) {
    status = POINT;
  } else if (found >= 11 && found <= 12) {
    status = PLUS_MINES;
  } else if (found >= 13 && found <= 16) {
    status = OTHER_BINARY;
  } else if (found == 17) {
    status = OPEN_BRACE;
  } else if (found == 18) {
    status = CLOSE_BRACE;
  } else if (found >= 19 && found <= 23) {
    status = FIRST_FUN_SYMBOL;
  } else if (found >= 24 && found <= 29) {
    status = OTHER_FUN_SYMBOL;
  } else if (found == 30) {
    status = X;
  } else if (found == 31) {
    status = E;
  }
  return status;
}

bool s21::Model::FuncParcer_(char symbol, bool &last_f_symbol) {
  std::string f_pattern1 =
      "ln---ncos--csin--stan--tlog--lacos-Aasin-Satan-Tsqrt-q";
  std::string pattern = "coigqrtsaln";
  std::string pattern_first_s = "ctsal";
  bool res = true;
  if (pattern.find(symbol) != std::string::npos) {
    std::string t_str = (i_str_ + symbol);
    int shift = 1;
    for (int i = i_str_.size() - 1;
         i >= 0 && (i_str_[i] >= 'a' && i_str_[i] <= 't'); i--) {
      shift++;
    }
    if (shift == 1) {
      if (pattern_first_s.find(symbol) == std::string::npos)
        res = false;
    }
    if (shift > 1) {
      size_t f_found = std::string::npos;
      std::string t_sub_str = t_str.substr((t_str.size() - shift), shift);
      f_found = (f_pattern1).find(t_sub_str); // if mistakes - need to check if
                                              // substr>than last part
      res = (f_found != std::string::npos) && (f_found % 6 == 0);
      if (res && f_pattern1[f_found + shift] == '-') {
        last_f_symbol = true;
      }
    }
  }
  return res;
}

bool s21::Model::CheckNotRepeatInNumber_(char symbol) {
  bool check_pass = true;
  bool stop_symbol = false;
  if (!i_str_.empty()) {
    for (int i = i_str_.size() - 1; i >= 0 && !stop_symbol; i--) {
      if (i_str_[i] == symbol) {
        stop_symbol = true;
        check_pass = false;
      } else if (i_str_[i] < '0' ||
                 i_str_[i] >
                     '9') { // every symbol that not number will stop alghoritm
        stop_symbol = true;
      }
    }
  }
  return check_pass;
}

bool s21::Model::NotForbSymInBegin_(int curr_symb_status,
                                    int prev_symb_status) {
  return !((prev_symb_status == EMPTY || prev_symb_status == OPEN_BRACE) &&
           (curr_symb_status == OTHER_BINARY ||
            curr_symb_status == OTHER_FUN_SYMBOL ||
            curr_symb_status == CLOSE_BRACE));
}

bool s21::Model::NotRepeating_(int curr_symb_status, int prev_symb_status,
                               char symbol) {
  return curr_symb_status == DIGIT || curr_symb_status == PLUS_MINES ||
         curr_symb_status == OPEN_BRACE || curr_symb_status == CLOSE_BRACE ||
         prev_symb_status == EMPTY || symbol != i_str_[(i_str_.length() - 1)];
}

bool s21::Model::BraceCounterOk_() {
  int count_open_br = 0;
  int count_close_br = 0;
  for (auto ch : i_str_) {
    if (ch == '(')
      count_open_br++;
    if (ch == ')')
      count_close_br++;
  }
  return (count_open_br - count_close_br > 0);
}

// this alghoritm check every symbol before adding it to str, in the places
// where user inserts symbol without bop 123x it will add * and finally it 123*x
bool s21::Model::PreParcer_(char symbol) {
  int css = StatusSymb_(symbol); // css- current_symbol_status
  int pss = (i_str_.empty()
                 ? EMPTY
                 : StatusSymb_(i_str_[(i_str_.length() -
                                       1)])); // pss - previous_symbol_status
  bool res = false;
  if (css != FORBIDDEN) { // every symbol that can be
    res = true;
    if (NotRepeating_(css, pss, symbol)) {
      res = NotForbSymInBegin_(css, pss);
    } else {
      res = false;
    }
    if (res) {
      if ((pss == PLUS_MINES || pss == OTHER_BINARY) && css == OTHER_BINARY) {
        res = false;
      } else if (pss == PLUS_MINES && css == PLUS_MINES) {
        res = false;
      } else {
        bool last_function_symbol = false;
        if (css == POINT && pss != E) {

          res = CheckNotRepeatInNumber_(symbol);
        } else if ((pss == DIGIT && (css == FIRST_FUN_SYMBOL ||
                                     css == OPEN_BRACE || css == X)) ||
                   (pss == CLOSE_BRACE &&
                    (css == DIGIT || css == FIRST_FUN_SYMBOL || css == E ||
                     css == X || css == OPEN_BRACE)) ||
                   (pss == X &&
                    !(css == OTHER_BINARY || css == PLUS_MINES ||
                      css == CLOSE_BRACE) &&
                    css != E)) {
          i_str_ += '*';
        } else if (pss != DIGIT &&
                   (css == OTHER_FUN_SYMBOL || css == FIRST_FUN_SYMBOL)) {
          res = FuncParcer_(symbol, last_function_symbol);
        } else if ((pss == FIRST_FUN_SYMBOL || pss == OTHER_FUN_SYMBOL) &&
                   !(css == FIRST_FUN_SYMBOL || css == OTHER_FUN_SYMBOL)) {
          res = false;
        } else if ((pss == OTHER_BINARY || pss == PLUS_MINES ||
                    !BraceCounterOk_()) &&
                   (css == CLOSE_BRACE)) {
          res = false;
        } else if ((pss != DIGIT && css == E) ||
                   (pss == E && !(css == DIGIT || css == PLUS_MINES)) ||
                   (pss == DIGIT && css == E &&
                    (!CheckNotRepeatInNumber_('E')))) {
          res = false;
        }

        if (pss == PLUS_MINES && i_str_.size() > 1 &&
            i_str_[i_str_.size() - 2] == 'E' && css != DIGIT) {
          res = false;
        }
        if (pss == POINT && css != DIGIT) {
          if (((i_str_[i_str_.size() - 2] < '0') ||
               (i_str_[i_str_.size() - 2] > '9')) ||
              (i_str_.size() == 1)) {
            res = false;
          } else if (css == X || css == OPEN_BRACE) {
            i_str_ += '*';
          } else if (css == E) {
            res = true;
          }
        }

        if (res)
          i_str_ += symbol;
        if (last_function_symbol)
          i_str_ += '(';
      }
    }
  }
  return res;
}

int s21::Model::SymbolParcer_(int *symbol, size_t *iterator) {
  std::string s_pattern = "-+~#/*^)(%";
  int res = 0;
  char symb = 'd';
  size_t shift = 2;
  if (s_pattern.find(*symbol) == std::string::npos) {
    size_t f_found = std::string::npos;
    std::string f_pattern1 = "ln---n";
    std::string f_pattern2 = "cos--csin--stan--tlog--lmod--%";
    std::string f_pattern3 = "acos-Aasin-Satan-Tsqrt-q";
    while (shift != 5 && f_found == std::string::npos) {
      std::string *f_pattern = nullptr;
      if (shift == 2)
        f_pattern = &f_pattern1;
      if (shift == 3)
        f_pattern = &f_pattern2;
      if (shift == 4)
        f_pattern = &f_pattern3;
      std::string substr = i_str_.substr(*iterator, shift);
      f_found = (*f_pattern).find(substr);

      bool found_and_inside_cell =
          (f_found != std::string::npos) && (f_found % 6 == 0);
      if (found_and_inside_cell) {
        symb = (*f_pattern)[f_found + 5];
        (*iterator) += (shift - 1);
      }
      shift++;
    }
    res = f_found == std::string::npos ? 1 : 0;
    (*symbol) = symb;
  }
  return res;
}

std::string s21::Model::CrStackElem_(char symbol) {
  char priority = ' ';
  std::string res = "";
  if (symbol == '^') {
    priority = ULTRA;
  } else if (symbol == '#' || symbol == '~') {
    priority = EXTRAHIGH;
  } else if (std::string("#~sctTqSlnA").find(symbol) != std::string::npos) {
    priority = HIGH;
  } else if (symbol == '*' || symbol == '/' || symbol == '%') {
    priority = MEDIUM;
  } else if (symbol == '+' || symbol == '-') {
    priority = LOW;
  } else if (symbol == '(' || symbol == ')') {
    priority = EXTRALOW;
  }
  res += symbol;
  res += priority;
  res += '|';
  return res;
}

std::string s21::Model::CreateRPN_() {
  int now;
  std::string stack;
  std::string o_str;
  int space = 0;
  int res = 0;
  int after_digit = 0;
  for (size_t i = 0; i < i_str_.size(); i++) {
    now = i_str_[i];
    if ((now >= '0' && now <= '9') || now == '.' || now == 'x' || now == 'E' ||
        i_str_[i - 1] == 'E') {
      if (space)
        o_str += ' ';
      o_str += char(now);
      space = 0;
      after_digit = 1;
    } else if (SymbolParcer_(&now, &i) == 0) {
      if (after_digit == 0) {
        if (now == '-')
          now = '~';
        if (now == '+')
          now = '#';
      }
      std::string element = CrStackElem_(now);
      space = 1;
      if (now != ')')
        after_digit = 0;
      int brace_terminate = 0;
      if (!stack.empty()) {
        while (!stack.empty() && stack[1] >= element[1] && now != '(' &&
               !brace_terminate) {
          brace_terminate = (now == ')' && stack[0] == '(');
          if (stack[0] != '(') {
            o_str += ' ';
            o_str += stack.substr(0, 1);
          }
          stack.erase(0, 3);
        }
      }
      res += (brace_terminate == 0 && now == ')');
      if (now != ')') {
        stack.insert(0, element);
      }
    }
  }
  while (!stack.empty()) {
    if (stack[0] == '(' || stack[0] == ')') {
      res++;
    }
    o_str += ' ';
    o_str += stack.substr(0, 1);
    stack.erase(0, 3);
  }
  if (res > 0) {
    o_str.clear();
    o_str += "Error";
  } else if (o_str[0] == ' ') {
    o_str.erase(0, 1);
  }
  if (o_str == ".")
    o_str = "0";
  return o_str;
}

void s21::Model::PushStack_(doubles **p, double value) {
  doubles *new_node = new doubles;
  new_node->value_ = value;
  new_node->next = *p;
  *p = new_node;
}

double s21::Model::PopStack_(doubles **p) {
  double x = 0;
  if (p) {
    doubles *temp = *p;
    x = (*p)->value_;
    *p = (*p)->next;
    delete temp;
  }
  return x;
}

double s21::Model::ArgProcessing_(int symbol, doubles **stack) {
  double result = 0;
  if (symbol == '-') {
    double operand_1 = PopStack_(stack);
    double operand_2 = PopStack_(stack);
    result = operand_2 - operand_1;
  } else if (symbol == '^') {
    double operand_1 = PopStack_(stack);
    double operand_2 = PopStack_(stack);
    result = pow(operand_2, operand_1);
  } else if (symbol == '+')
    result = PopStack_(stack) + PopStack_(stack);
  else if (symbol == '*')
    result = PopStack_(stack) * PopStack_(stack);
  else if (symbol == '/') {
    double operand_1 = PopStack_(stack);
    double operand_2 = PopStack_(stack);
    result = operand_2 / operand_1;
  } else if (symbol == '%') {
    double operand_1 = PopStack_(stack);
    double operand_2 = PopStack_(stack);
    result = fmod(operand_2, operand_1);
  } else {
    result = UnaryOperations_(symbol, stack);
  }
  return result;
}

double s21::Model::UnaryOperations_(int symbol, doubles **stack) {
  double result = 0;
  if (symbol == '~')
    result = -1 * PopStack_(stack);
  else if (symbol == '#')
    result = PopStack_(stack);
  else if (symbol == 's')
    result = std::sin(PopStack_(stack));
  else if (symbol == 'c')
    result = std::cos(PopStack_(stack));
  else if (symbol == 'A')
    result = std::acos(PopStack_(stack));
  else if (symbol == 't')
    result = std::tan(PopStack_(stack));
  else if (symbol == 'T')
    result = std::atan(PopStack_(stack));
  else if (symbol == 'S')
    result = std::asin(PopStack_(stack));
  else if (symbol == 'q')
    result = std::sqrt(PopStack_(stack));
  else if (symbol == 'n')
    result = std::log(PopStack_(stack));
  else if (symbol == 'l')
    result = std::log10(PopStack_(stack));
  return result;
}

int s21::Model::ProcessingRpn_(std::string i_str, double x_value,
                               double &result) {
  double value1 = 0;
  int res = 0;
  doubles *first = nullptr;
  std::size_t pos = 0;
  for (std::size_t i = 0; (i < i_str.size()) && res == 0; i++) {
    int now = i_str[i];
    if ((i_str[i] >= '0' && i_str[i] <= '9') || i_str[i] == '.' ||
        i_str[i] == 'e') {
      try {
        value1 = std::stod(i_str.substr(i), &pos);
      } catch (const std::out_of_range &oor) {
        std::cerr << "double out_of_range: " << oor.what() << '\n';
        res = 2;
      }
      i = (i + pos);
      PushStack_(&first, value1);
    } else if (i_str[i] == 'x') {
      PushStack_(&first, x_value);
    } else if (i_str[i] == ' ') {
    } else {
      int stack_elements = StackElemCounter_(first);
      if ((stack_elements < 2 && (now == '-' || now == '+' || now == '*' ||
                                  now == '/' || now == '%' || now == '^')) ||
          stack_elements == 0) {
        res += 1;
        break;
      } else {
        result = ArgProcessing_(now, &first);
        PushStack_(&first, result);
      }
    }
  }
  int values = 0;
  if (res == 0 && first && !first->next) {
    result = first->value_;
  }
  while (first) {
    doubles *temp = first;
    first = first->next;
    delete temp;
    values++;
  }
  res += (values > 1 ? 1 : 0);

  return res;
}

int s21::Model::StackElemCounter_(doubles *stack) {
  int res = 0;
  while (stack) {
    stack = stack->next;
    res++;
  }
  return res;
}
