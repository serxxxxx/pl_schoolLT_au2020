vuser_init (){
	
	
	char *VtsServer = "{VTS_server}"; //ip your machine
  	int nPort = 8888; //порт instance
  	
	lrvtc_connect(VtsServer, nPort, VTOPT_KEEP_ALIVE); // connection VTS
	return 0;
}