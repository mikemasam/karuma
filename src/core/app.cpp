namespace core {
    static std::string app::env(std::string name, std::string _default){
      std::string v = dotenv::env[name];
      return v.empty() ? _defualt : v; 
    }
}
