vuser_init()
{	
	char *VtsServer = "http://localhost";
	int nPort = 3333;
	int rc;
	
	lrvtc_connect(VtsServer,nPort,VTOPT_KEEP_ALIVE);
	
	//��� �������
	//rc = lrvtc_connect(VtsServer,nPort,VTOPT_KEEP_ALIVE);
	//lr_log_message("Connect result rc=%d\n", rc);
	
	return 0;
}
