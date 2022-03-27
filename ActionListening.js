$( document ).ready(function(){ //Beim Seitenaufbau den switch an den status anpassen.
  if (state_front == 1){
    $("#front").prop("checked", true);
  }
  else{
    $("#front").prop("checked", false);
  }
  
  if (state_rear == 1){
    $("#rear").prop("checked", true);
  }
  else{
    $("#rear").prop("checked", false);
  }
  
  
  // 1. Switch
  $("#front").click(function(){
    if ($("#front").prop("checked")){ //wenn "an"
      $.post("setData.php" , { id: "1", status: "1" }, function(response){
          console.log("Response: " + response);
        });
    }
    else{ //wenn "aus"
      $.post("setData.php" , { id: "1", status: "0" }, function(response){
          console.log("Response: " + response);
      });
    }
  });
  
  // 2. switch  
  $("#rear").click(function(){
    if ($("#rear").prop("checked")){
      $.post("setData.php" , { id: "2", status: "1" }, function(response){
          console.log("Response: " + response);
      });
    }
    else{
      $.post("setData.php" , { id: "2", status: "0" }, function(response){
          console.log("Response: " + response);
      });
    }
  });
});


