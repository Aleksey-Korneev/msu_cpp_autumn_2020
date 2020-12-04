InvalidFormat::InvalidFormat(const std::string& message_): message(message_)
{
}

InvalidValue::InvalidValue(const std::string& message_): message(message_)
{
}

void unpack_template_args(std::vector<std::string>&)
{
}

template<class T>
void unpack_template_args(
        std::vector<std::string>& template_args, const T& arg)
{
    std::stringstream s;
    s << arg;
    template_args.push_back(s.str());
}

template<class T, class... Args>
void unpack_template_args(std::vector<std::string>& template_args, const T& arg, const Args&... args)
{
    unpack_template_args(template_args, arg);
    unpack_template_args(template_args, args...);
}

template<class... Args>
std::string format(const std::string& str, const Args&... args)
{
    std::vector<std::string> template_args;
    unpack_template_args(template_args, args...);
    std::ostringstream res;
    size_t opening_brace = str.find("{", 0);
    size_t closing_brace = str.find("}", 0);
    size_t pos = 0;
    while (opening_brace != std::string::npos && closing_brace != std::string::npos) {
        if (opening_brace > closing_brace) {
            throw InvalidFormat("Unexpected closing brace.");
        }
        if (str.find("{", opening_brace + 1) < closing_brace) {
            throw InvalidFormat("Unexpected opening brace.");
        }   
        res << str.substr(pos, opening_brace - pos);
        int arg_num = stoi(str.substr(opening_brace + 1, closing_brace - 1 - opening_brace));
        if (arg_num < 0 || static_cast<size_t>(arg_num) >= template_args.size()) {
            throw InvalidValue("Argument index out of range.");
        }
        res << template_args[arg_num];
        pos = closing_brace + 1;
        opening_brace = str.find("{", opening_brace + 1);
        closing_brace = str.find("}", closing_brace + 1);
    }
    if (opening_brace == std::string::npos && closing_brace == std::string::npos) {
        res << str.substr(pos, str.size() - pos);
        return res.str();
    } else if (opening_brace == std::string::npos) {
        throw InvalidFormat("Unexpected closing brace.");
    } else {
        throw InvalidFormat("Unexpected opening brace.");
    }
}
