#🚀 Running Gemini AI on ESP8266! 🚀

- it to process and respond to user queries in real time! 
  By leveraging Postman API and programming via Arduino IDE, 
  I was able to send questions to Gemini AI and receive intelligent responses directly on the serial monitor.

#💡 Key Highlights:
✅ ESP8266 + Gemini AI API integration
✅ Real-time AI-powered responses over serial communication
✅ Postman API for seamless data exchange
✅ Embedded AI applications using a microcontroller

- This project showcases how AI and IoT can work together to bring intelligence to embedded systems. Excited to explore more possibilities! 🚀

- Would love to hear thoughts from the community—how do you see AI being used in microcontrollers? 🤖💡


#How to Run:
- Open ArduinoIDE and paste code provided in Repository.
- Give Your wifi network user name and password in the dedicated variables in the code.
- Get your Gemini API Key from https://ai.google.dev/gemini-api/docs and paste that API KEY in 'Gemini_Token' variable.
- Copy 'String url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=" + String(Gemini_Token);' in your code.
- Download PostmanAPI and open it paste the String URL in URL area and select "POST"  and hit send.
- Go to headers down there and select all the headers .
- make sure you've entered 'Content-Type : application/json'
  
- Go to Body beside Headers Section and enter the below code
# {
    {
    "contents":[{
        "parts":[{
            "text": "Ask Anything:" }]
    }],
    "generationConfig":{
        "maxOutputTokens": 100
    } 
    }
}
- That's All you Can upload the code to NodeMCU ESP8266
  select port number and upload
- open serial monitor and you can type and get respones to your questions.

## License  
📜 MIT License  
