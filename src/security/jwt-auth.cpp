namespace security {
  std::string JwtAuth::create(int seconds){
    std::string token = jwt::create()
      .set_issuer(app::env("jwt_issuer","auth0"))
      .set_issued_at(std::chrono::system_clock::now())
      .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{seconds})
      .set_payload_claim("sample", std::string("test"))
      .sign(jwt::algorithm::hs256{app::env("jwt_secret","1234567890")});
    return token;
  }
}
