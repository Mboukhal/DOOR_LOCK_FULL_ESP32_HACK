#include "./config_page.hpp"

WiFiServer server(80);


void ConfigPage::begin(WifiLock *WL) {

  this->WL = WL;

    // Connect to WiFi
  WiFi.softAP(SSID_AP, PASSWORD_AP);
  WiFi.softAPConfig(IPAddress(192, 168, 13, 37), IPAddress(192, 168, 13, 1), IPAddress(255, 255, 255, 0));

  // Print the ESP32 IP address
  Serial.println("ESP32 IP address:");
  Serial.println(WiFi.softAPIP());

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void ConfigPage::waitClient(void) {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");
    this->handleClient(client);
  }
}

void ConfigPage::handleClient(WiFiClient client) {


  Serial.println("New Client.");
    // this->WL.print_auth_data();


  String currentLine = "";

  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      // Serial.write(c);
      this->header += c;

      if (c == '\n') {
        if (currentLine.length() == 0) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();

          if (this->header.indexOf("GET /submit") >= 0) {
            handleFormSubmission();
          }

          displayHtmlForm(client);

          break;
        } else {
          currentLine = "";
        }
      } else if (c != '\r') {
        currentLine += c;
      }
    }
  }
  this->header = "";
  client.stop();
  // Serial.println("Client disconnected.");
  // Serial.println("");
}

void ConfigPage::handleFormSubmission() {

  int ssid_index = this->header.indexOf("ssid=");
  int password_index = this->header.indexOf("password=");
  int endpoint_index = this->header.indexOf("endpoint=");
  int token_index = this->header.indexOf("token=");
  int http_index = this->header.indexOf(" HTTP/");

  if (ssid_index >= 0 && password_index >= 0 && endpoint_index >= 0 && token_index >= 0) {
    this->ssid = this->header.substring(ssid_index + 5, password_index - 1);
    this->password = this->header.substring(password_index + 9, endpoint_index - 1);
    this->endpoint = this->header.substring(endpoint_index + 9, token_index - 1);
    this->token = this->header.substring(token_index + 6, http_index);

    // Serial.println("--------------------------------------------------------");
    // Serial.println(this->ssid + ", " + this->password + ", " + this->endpoint + ", "  + this->token);
    // Serial.println("--------------------------------------------------------");

    // this->WL->set_auth_data(this->ssid, this->password, this->endpoint, this->token);
    this->WL->print_auth_data();
  }

}

// GET /submit?ssid=zdf&password=ag&endpoint=adfg&token=ag HTTP/1.1


void ConfigPage::displayHtmlForm(WiFiClient client) {

  client.println(R"(
<!DOCTYPE html>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <style>
        body {
            background-color: black;
            color: lime;
            font-family: 'Courier New', monospace;
            text-align: center;
        }

        h1 {
            color: red;
        }

        form {
            display: inline-block;
            text-align: left;
            margin: 20px;
        }

        label {
            display: inline-block;
            width: 100px;
            text-align: right;
            margin-right: 10px;
        }

        input[type='text'] {
            background-color: black;
            color: lime;
            border: 1px solid lime;
            padding: 5px;
            margin-bottom: 10px;
            width: 250px;
        }

        input[type='submit'] {
            background-color: lime;
            color: black;
            border: 1px solid lime;
            padding: 10px;
            cursor: pointer;
            float: right;
        }
    </style>
</head>

<body>
    <h1>Config Door Lock 1337 Server</h1>
    <form action="/submit" method="get" onsubmit='return validateForm()'>
        <label for="ssid">SSID:</label>
        <input type="text" name="ssid" id="ssid" value=""><br>

        <label for="password">PASSWORD:</label>
        <input type="text" name="password" id="password" value=""><br>

        <label for="endpoint">ENDPOINT:</label>
        <input type="text" name="endpoint" id="endpoint" value=""><br>

        <label for="token">TOKEN:</label>
        <input type="text" name="token" id="token" value=""><br>

        <input type="submit" value="Submit">
    </form>

    <script>
        function validateForm() {
            var ssid = document.getElementById("ssid").value;
            var password = document.getElementById("password").value;
            var endpoint = document.getElementById("endpoint").value;
            var token = document.getElementById("token").value;

            if (ssid.trim() === '' || password.trim() === '' || endpoint.trim() === '' || token.trim() === '') {
                alert("All fields must be filled out");
                return false;
            }

            return true;
        }
    </script>
</body>

</html>
)");
  client.println();
}
