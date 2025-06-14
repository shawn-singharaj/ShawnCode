Microservice for Ben's Study Manager by Shawn Singharaj

PURPOSE/INTRO:
Implemented a database to save, access, update, and delete saved study sessions using MongoDB as the database of choice. Two JavaScript programs are used to implement these "CRUD" HTTP operations to use the database to save these study sessions. 

A study session contains the following parameters, all required:
 - name: Name of the study session
 - full_dur: Full length of the study session
 - num_breaks: Number of breaks in the full study session
 - break_dur: Length of each break 
 - long_break_dur: Length of the long break following Pomodoro Technique
 - study_dur: Length of each study session
 - study_link: String for the link to media for study session
 - break_link: String for link to media for break session

Dependencies:
  1. MongoDB extension on VSCode and/or use web browser: cloud.mongodb.com - My project is called "Audio Study Aid"
      To connect to cluster: mongodb+srv://studyaid:cs361@cluster0.ffligwb.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0
  2. Node.js to connect to server
  3. To use test file, REST Client extension on VSCode

Set-Up:
  1. Open the folder in VSCode, make sure node is installed
  2. run "npm install" in terminal
  3. Go to MongoDB extension and connect to a cluster, pasting "mongodb+srv://studyaid:cs361@cluster0.ffligwb.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0"
  4. Make sure the server is live by clicking on the leaf/cluster (should turn green), now database server is live, ready to be connected
  5. run "npm start" and the REST API/Node should be connected to the MongoDB database.
  6. Use the test requests file to perform CRUD operations  

Requesting Data:
   To test the HTTP responses, a test_requests.http file has been provided to send requests that post, get, update, and delete the study sessions if you'd like to use it. After setting up, just change the request bodies (i.e. name, num_breaks, etc.) as desired and click "send request" above the request headers. Then it should state that it has sent the request.

Example request:
      POST http://localhost:3000/studysessions HTTP/1.1
      content-type: application/json
      
      {
          "name": "Study Session Example",
          "full_dur": 200,
          "num_breaks": 4,
          "break_dur": 5,
          "long_break_dur": 20,
          "study_dur": 25,
          "study_link": "https://youtu.be/rBpApqtG7Us?si=kwFthg-jaZMDUKuO",
          "break_link": "https://youtu.be/rBpApqtG7Us?si=kwFthg-jaZMDUKuO" 
      }


Receiving Data: 
  After setting up, after sending a request on the test_requests.http file, a new window will open with the response body containing the parameters of each study session, response code, and other response details. These changes will be reflected on the MongoDB database.

Example response:
      HTTP/1.1 201 Created
      X-Powered-By: Express
      Content-Type: application/json; charset=utf-8
      Content-Length: 280
      ETag: W/"118-1QfN7MDONisqR9HMZmcJQJtzHz8"
      Date: Tue, 20 May 2025 00:06:33 GMT
      Connection: close
      
      {
        "name": "Study Session Example",
        "full_dur": 200,
        "num_breaks": 4,
        "break_dur": 5,
        "long_break_dur": 20,
        "study_dur": 25,
        "study_link": "https://youtu.be/rBpApqtG7Us?si=kwFthg-jaZMDUKuO",
        "break_link": "https://youtu.be/rBpApqtG7Us?si=kwFthg-jaZMDUKuO",
        "_id": "682bc789715a17fe0907a034",
        "__v": 0
      }
![Screenshot 2025-05-19 172628](https://github.com/user-attachments/assets/cef77363-d37b-4896-acbb-0837ae2f0ff9)


     
