# UE4_SocketHelper
ue4 socket client plugin , only support receive data ;



use : new class inherit the socket actor class , and override the CF_ReceiveData() function;



note : you will call game logic in GameThread , or will cause crash ;

