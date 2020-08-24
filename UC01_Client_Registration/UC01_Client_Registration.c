UC01_Client_Registration()
{

  char *VtsServer = "{currentIP}"; //указывайте свой IP
  int nPort = 1862; //порт instance
	  lrvtc_connect(VtsServer,nPort,VTOPT_KEEP_ALIVE); //connect to vts
	  

  lrvtc_retrieve_message("Email_client_reg"); //???????? ? ?????????? email ?????? ???????? ?? ???????????? ???????
  lr_log_message("Retrieved value is: %s", lr_eval_string("{Email_client_reg}")); //???????
  lrvtc_send_message("Email_client_auth", "{Email_client_reg}");//?????????? ? ??????? db_clients ????????? ????????? raw_clients
  
	
	
	web_set_sockets_option("SSL_VERSION", "TLS1.2");

	lr_start_transaction("UC01_TR01_Open_Main_Page");

	web_url("loadtest.uxcrowd.ru", 
		"URL=https://loadtest.uxcrowd.ru/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t14.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC01_TR01_Open_Main_Page", LR_AUTO);
	
	
	lr_start_transaction("UC01_TR02_Reg_New_Client");
	
	web_url("modal-login.html", 
		"URL=https://loadtest.uxcrowd.ru/tmpl/tmpl_home/modal-login.html", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t24.inf", 
		"Mode=HTML", 
		LAST);

	web_reg_save_param_ex(
		"ParamName=xsrf",
		"LB=XSRF-TOKEN=",
		"RB=;",
		LAST);
	
	web_custom_request("account", 
		"URL=https://loadtest.uxcrowd.ru/api/account", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=1", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t24.inf", 
		"Mode=HTML", 
		LAST);
	

	web_add_auto_header("X-XSRF-TOKEN","{xsrf}");
	
	web_custom_request("register", 
		"URL=https://loadtest.uxcrowd.ru/api/register", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Mode=HTML", 
		"EncType=application/json;charset=UTF-8", 
		"BodyBinary={\"name\":\"{Name}\",\"position\":\"{Position}\",\"company\":\"{Company}\",\"email\":\"{Email_client_reg}\",\"telNumber\":\"\+7{phone_part1}-{phone_part2}-{phone_part3}\",\"site\":\"{Test_site}\",\"role\":\"ROLE_CUSTOMER\"," "\"tariffType\":\"PROJECT\"}",LAST);
	

	lr_end_transaction("UC01_TR02_Reg_New_Client", LR_AUTO);
	

	
//	web_revert_auto_header("X-XSRF-TOKEN");
//
//	web_add_header("X-XSRF-TOKEN", 
//		"fd3b09f7-5bb6-47b1-aa5f-091044328f9b");


lr_start_transaction("UC01_TR03_DB_update");

  lr_db_connect("StepName=connectBD",
        "ConnectionName=connection",
        "ConnectionString=Driver={PostgreSQL Unicode};Database=do-prod;Server=loadtest.uxcrowd.ru;Port=5432;Uid=do-prod;Pwd=do-prod;",
        "ConnectionType=ODBC",
        LAST);

 lr_db_executeSQLStatement("StepName=updatePassword", 
                      "ConnectionName=connection", 
                      "SQLStatement=update users set password = '$2a$10$lDyjp2iJ2HhWwrDHI5q37O32CIVqENgrztOCxGyCoJqT7TbxzXX92' where email = '{Email_client_reg}';",
                      "DatasetName=MyDataset",
                      LAST );
  
  lr_db_executeSQLStatement("StepName=updateTariffType", 
                      "ConnectionName=connection", 
                      "SQLStatement=update customer_tariff_link set customer_tariff_id = (select id from customer_tariff where name = 'BUSINESS'), our_testers_remain = 99, their_testers_remain = -1, active = true, end_date = current_date + interval '3 month' where customer_id = (select id from users where email = '{Email_client_reg}');",
                      "DatasetName=MyDataset",
                      LAST );


lr_db_disconnect("StepName=disconnectBD","ConnectionName=connection",LAST);

lr_end_transaction("UC01_TR03_DB_update", LR_AUTO);

	
	return 0;
}