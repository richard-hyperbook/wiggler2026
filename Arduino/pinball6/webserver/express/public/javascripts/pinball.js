      var buf = "";
      function actionEvent(event){
      var dataString = event.data;
        //- console.log("(Z9A)");
        //- console.log(dataString); 
        var dataString = event.data;
        if (dataString.length < 2){
          if (dataString[0] == "+"){
            dataString = buf;
            buf = "";
          } else {
            buf = buf + dataString;
            return;
          }              
        } 
        var j = 0;
        for(j = 0; j < dataString.length; j = j + 2){
        var eIndexString = dataString[j];
        var digitString = dataString[j + 1];
        var actionString = dataString.substring(j, j + 2);
         console.log("(Z20)",actionString.length, '*', actionString);
        var eChar = eIndexString.charCodeAt(0);
        eIndex = eChar - 'A'.charCodeAt(0);
        console.log("(Z1)", eChar);
        if (isNaN(eIndex) || ((eIndex < 0) || (eIndex > 26))) {
          console.log("(Z4)", eIndex);
        } else { 
          digit = parseInt(digitString);
          console.log("(Z2)" + digit);
        if (isNaN(digit) || ((digit < 0) || (digit > 9))) {
          console.log("(Z3)" + digit);
          } else {
            var i;
            if ((eIndex >= 0) && (eIndex <= 15)){
              let e = document.getElementById(eIndexString);
              e.innerHTML = digitString; 
            } else {
              console.log("(Z100)" + eIndexString + "%" + digitString);
              switch(eIndexString){
                case('Q'):
                  var x = 0;
                  var y = 0;
                  for(y = 0; y < 4; y++){
                    for(x = 0; x < 4; x++){
                      let idIndex = x + (4 * y);
                      let idChar = String.fromCharCode('A'.charCodeAt(0) + idIndex);
                      console.log('(Z102)'+idIndex.toString()+'&'+idChar); 
                      let e = document.getElementById(idChar);
                      if(y == (digit - 1)){
                        e.style.color = 'yellow';
                      } else {
                        e.style.color = 'grey';
                      }
                    }
                  }
                  break;
                case('R'):
                  let ee = document.getElementById("GAMEOVER");
                  console.log("(Z101)");
                  if(digit == 0){
                    ee.style.color='black';
                  } else {
                    ee.style.color='white';                    
                  }
                  break;
                case('S'):
                  let eee = document.getElementById("INPLAY");
                  eee.style.color = 'white';
                  eee.innerHTML = "BALL: " + digitString;
                  break; 
                case('T'):
                  let eeee = document.getElementById("CANPLAY");
                  eeee.style.color = 'blue';
                  eeee.innerHTML = digitString + " CAN PLAY";
                  break;
               default:
                 break;
              }  
            }
            for(i = 0; i < A.length; i++){
              //- console.log("(Z6A)", i, Event);
              //- console.log("(Z6B)", dataString, A[i][Event]);
              if (actionString == A[i][Event]){
                 console.log("(Z0)", i, "*", A[i][Name]);
                 let e = document.getElementById(A[i][Name]);  
                 e.style.position = "absolute";
                 e.style.scale = A[i][Scale].toString(); 
                 e.style.left = A[i][Left].toString() + "px";
                 e.style.top =  A[i][Top].toString() + "px";
                 e.style.clipPath = "inset(" + 
                   A[i][InsetTop].toString() + "px " +  
                   A[i][InsetRight].toString() + "px " +  
                   A[i][InsetBottom].toString() + "px " +  
                   A[i][InsetLeft].toString() + "px)";
                 console.log("(Z7)", i, "*", e.style.clipPath);  
              }
            }
          }
        }
        }
      }

      function setup(){
        const t = ["A0","B0","C0","D0","E0","F0","G0","H0","I0","J0","K0","L0",
                 "M0","N0","O0","P0","Q0","R1","S0"];
        var i = 0;
        console.log("(Y0)");
        for (i = 0; i < t.length; i++){  
          var e = new MessageEvent('message', {data: t[i]});
          actionEvent(e); 
        }
      }
      function test(id) {
        const target = document.getElementById("target");
        var e = new MessageEvent('message', {data: "I1"});
        actionEvent(e); 
        var e = new MessageEvent('message', {data: "J2"});
        actionEvent(e);
        var e = new MessageEvent('message', {data: "K3"});
        actionEvent(e);
        var e = new MessageEvent('message', {data: "L4"});
        actionEvent(e); 
        var e = new MessageEvent('message', {data: "M1"});
        actionEvent(e); 
        var e = new MessageEvent('message', {data: "N2"});
        actionEvent(e);
        var e = new MessageEvent('message', {data: "O3"});
        actionEvent(e);
        var e = new MessageEvent('message', {data: "P4"});
        actionEvent(e); 
      }
      const ws = new WebSocket("ws://wiggler:8080");
      ws.addEventListener("open", () =>{
      console.log("(19)");
        ws.send("How are you?");
      });
      
      ws.addEventListener('message', function (event) {
        //- console.log("(20)" + event.data);
        //- console.log(event);
           actionEvent(event);
        }
      );  
