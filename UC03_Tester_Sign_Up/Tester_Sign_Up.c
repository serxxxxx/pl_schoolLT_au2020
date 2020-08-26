Tester_Sign_Up(){
	
	
	lrvtc_retrieve_message("email_tester_reg"); // put the variable "email" in the value of the same name
	
  	lr_log_message("Retrieved value is: %s", lr_eval_string("{email_tester_reg}")); // look value "email"
  	
  	lrvtc_send_message("email_authentication_tester", "{email_tester_reg}"); // adding the last value "email_test_reg" to the "email_authentication_tester" column

	web_set_sockets_option("SSL_VERSION", "TLS1.2");

	//correlation token	
	web_reg_save_param_ex(
     	"ParamName=token", 
     	"LB/IC=Set-Cookie: XSRF-TOKEN=",
     	"RB/IC=;",
  		LAST);
	
	lr_start_transaction("UC03_TC01_open_site_uxcrowd");

	web_url("{host}", 
		"URL=https://{host}/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t3.inf", 
		"Mode=HTML", EXTRARES,
		"Url=/api/account", ENDITEM,
		LAST);
	
	lr_end_transaction("UC03_TC01_open_site_uxcrowd", LR_AUTO);

	web_add_auto_header("X-XSRF-TOKEN", 
		"{token}");

	//registration tester
	lr_start_transaction("UC03_TC02_registration_tester");	
	
	web_custom_request("register",
		"URL=https://{host}/api/register", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://{host}/", 
		"Snapshot=t19.inf", 
		"Mode=HTML", 
		"EncType=application/json;charset=UTF-8", 
		"Body={\"email\":\"{email_tester_reg}\",\"role\":\"ROLE_NEW_TESTER\",\"tariffType\":null}", 
		LAST);
	lr_end_transaction("UC03_TC02_registration_tester", LR_AUTO);
  	
	lr_start_transaction("UC03_TC03_DB");
	lr_db_connect("StepName=connectBD",
        "ConnectionName=connection",
        "ConnectionString=Driver={PostgreSQL Unicode};Database=do-prod;Server=loadtest.uxcrowd.ru;Port=5432;Uid=do-prod;Pwd=do-prod;",
        "ConnectionType=ODBC",
        LAST);
	
	lr_db_executeSQLStatement("StepName=updatePassword", 
                      "ConnectionName=connection", 
                      "SQLStatement=update users set password = '$2a$10$lDyjp2iJ2HhWwrDHI5q37O32CIVqENgrztOCxGyCoJqT7TbxzXX92' where email = '{email_tester_reg}';",
                      "DatasetName=MyDataset",
                      LAST );
  
  	lr_db_executeSQLStatement("StepName=updateRole", 
                      "ConnectionName=connection", 
                      "SQLStatement=update users set role = 'ROLE_TESTER', gender = 'MALE', birthday = TO_DATE('08/02/2000', 'DD/MM/YYYY') where email = '{email_tester_reg}';",
                      "DatasetName=MyDataset",
                      LAST );
  
  	lr_db_executeSQLStatement("StepName=updateTesterData", 
                      "ConnectionName=connection", 
                      "SQLStatement=update tester set city = 'Russia', country = 'Pscov', family_status = 'NOT_MARRIED', fio = 'Ivanov Ivan Ivanovich', income = 40000, kids = 'NONE', education_id = 6, social_status_id = 3 where id = (select id from users where email = '{email_tester_reg}');",
                      "DatasetName=MyDataset",
                      LAST );
	
	lr_db_disconnect("StepName=Disconnect", "ConnectionName=connection", LAST );
	lr_end_transaction("UC03_TC03_DB", LR_AUTO);
	
	return 0;
}
