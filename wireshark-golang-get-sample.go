package main

import (
	"net/http"
	"crypto/tls"
	"os"
)

func main() {
  f, err := os.OpenFile("/tmp/keys", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0600)
  if err != nil {
    panic(err)
  }
  defer f.Close()

  client := &http.Client{
    Transport: &http.Transport{
      TLSClientConfig: &tls.Config{
        KeyLogWriter: f,
      },
    },
  }

  client.Get("https://auth.docker.io/token?service=registry.docker.io&scope=repository:node:pull")
}
