echo off

REM set working directory
cd ./review
REM start server and client
start /b "" "http://localhost:3000/"
node html/server/app.js
pause