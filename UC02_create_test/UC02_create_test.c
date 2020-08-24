UC02_create_test()
{

	web_set_sockets_option("SSL_VERSION", "TLS1.2");
	
	
	//take token from page
	 web_reg_save_param_ex(
	     "ParamName=token", 
	     "LB/IC=Set-Cookie: XSRF-TOKEN=",
	     "RB/IC=;",
 	 LAST);

	
	web_url("loadtest.uxcrowd.ru", 
		"URL=https://loadtest.uxcrowd.ru/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t69.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/api/account", ENDITEM, 
		LAST);

	//set taken token
	web_add_auto_header("X-XSRF-TOKEN", 
		"{token}");



	lr_think_time(16);


	lr_start_transaction("UC02_TR01_loginpage_open");
	
	//open page of autorisation 
	
	lr_think_time(18);

	web_url("modal-login.html", 
		"URL=https://loadtest.uxcrowd.ru/tmpl/tmpl_home/modal-login.html", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t81.inf", 
		"Mode=HTML", 
		LAST);



	lr_end_transaction("UC02_TR01_loginpage_open",LR_AUTO);

	lr_start_transaction("UC02_TR02_user_login");

	lr_think_time(27);
	
	//get token after autorisation 
	web_reg_save_param_ex(
	     "ParamName=token3", 
	     "LB/IC=Set-Cookie: XSRF-TOKEN=",
	     "RB/IC=; Path=",
	     "Ordinal=2",
 	 LAST);

	
	//sending form data of autorisation
	
	web_submit_data("authentication", 
		"Action=https://loadtest.uxcrowd.ru/api/authentication", 
		"Method=POST", 
		"TargetFrame=", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t82.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={username}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=remember-me", "Value=undefined", ENDITEM, 
		"Name=submit", "Value=Login", ENDITEM,
		EXTRARES, 
		"Url=/api/account", ENDITEM, 		
		LAST);

	web_revert_auto_header("X-XSRF-TOKEN");
	
	//set new token
	web_add_auto_header("X-XSRF-TOKEN", 
		"{token3}");
	
	//get info about user
	web_url("account", 
		"URL=https://loadtest.uxcrowd.ru/api/account", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t83.inf", 
		"Mode=HTML", 	
		LAST);

	
	
	//get the list of orders
	
	web_url("list-orders", 
		"URL=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t84.inf", 
		"Mode=HTML", 
		LAST);


	//get user info
	web_url("user", 
		"URL=https://loadtest.uxcrowd.ru/api/v2/tariff/user", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"Snapshot=t90.inf", 
		"Mode=HTML", 
		LAST);

	
	web_custom_request("orders", 
		"URL=https://loadtest.uxcrowd.ru/api/v3/customer/orders", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"Snapshot=t91.inf", 
		"Mode=HTML", 
		"EncType=application/json;charset=UTF-8", 
		"Body={\"direction\":\"DESC\",\"filter\":[\"ACTIVE\",\"COMPLETED\",\"DRAFT\",\"WAIT_CONFIRMATION\"],\"page\":0,\"size\":10,\"sort\":[\"startDate\"]}", 
		LAST);

	lr_end_transaction("UC02_TR02_user_login",LR_AUTO);

	lr_think_time(40);


	lr_start_transaction("UC02_TR03_newtest_open");


	lr_think_time(11);

	//page of creation order
	
	web_url("new.order.html", 
		"URL=https://loadtest.uxcrowd.ru/tmpl/tmpl_customer/new.order.html", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"Snapshot=t95.inf", 
		"Mode=HTML", 
		LAST);

	web_url("user_2", 
		"URL=https://loadtest.uxcrowd.ru/api/v2/tariff/user", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/order", 
		"Snapshot=t96.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/assets/css/svg/left-menu-icons/plus-active.svg", "Referer=https://loadtest.uxcrowd.ru/assets/gulp/sup_css.css", ENDITEM, 
		LAST);

	

	lr_think_time(7);


	lr_end_transaction("UC02_TR03_newtest_open",LR_AUTO);

	lr_think_time(40);

	lr_start_transaction("UC02_TR04_audince_open");


	lr_think_time(15);
	
	lr_save_int(rand() % 9999, "intro_num");
	
	
	
	//get orderId
	
	web_reg_save_param_regexp (
    "ParamName=orderId",
    "RegExp=(\\d{7,})",
	LAST );
	
	


	web_custom_request("draft", 
		"URL=https://loadtest.uxcrowd.ru/api/v2/customer/draft", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/order", 
		"Snapshot=t97.inf", 
		"Mode=HTML", 
		"EncType=application/json;charset=UTF-8", 
		"BodyBinary={\"introduction\":\"intro_texttttt{intro_num}\",\"targetSite\":\"https://wikipedia.org\",\"testTitle\":\"test-{intro_num}\",\"testType\":\"SITE\"}", 
		LAST);
	
	
	lr_end_transaction("UC02_TR04_audince_open",LR_AUTO);

	

	lr_think_time(4);
	lr_think_time(40);

	lr_start_transaction("UC02_TR05_tasks_open");

	//create random values
	lr_think_time(10);
	lr_save_int(rand()%40+10, "amount_people");
	lr_save_int(rand()%20+18, "min_age");
	lr_save_int(rand()%12+49, "max_age");
	
	//set audience info
	web_custom_request("updateOrderAudience", 
		"URL=https://loadtest.uxcrowd.ru/api/v2/customer/updateOrderAudience", 
		"Method=PUT", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/order?id={orderId}", 
		"Snapshot=t98.inf", 
		"Mode=HTML", 
		"EncType=application/json;charset=UTF-8", 
		"Body={\"orderId\":{orderId},\"testerType\":\"OUR\",\"participantGroupDTO\":[{\"ageRange\":{\"min\":{min_age},\"max\":{max_age}},\"children\":\"ANY\",\"count\":{amount_people},\"educations\":[\"COMMON\",\"MIDDLE_FULL\",\"MIDDLE_SPEC\",\"HIGH_NOT_FULL\",\"HIGH\"],\"familyStatus\":\"ANY\",\"gender\":\"ANY\",\"groupName\":\"name of segment\",\"incomeRange\":{\"min\":0,\"max\":55000},\"socialStatuses\":[\"STUDENT\",\"UNEMPLOYED\",\"HOUSEWIFE\",\"FREELANCER\",\"WORKER\",\"SPECIALIST\",\"CHIEF_DEPT\"],\"ordinal\":0}]}", 
		LAST);

	lr_think_time(9);


	lr_end_transaction("UC02_TR05_tasks_open",LR_AUTO);

	lr_think_time(40);

	lr_start_transaction("UC02_TR06_add_task");

	lr_end_transaction("UC02_TR06_add_task",LR_AUTO);



	lr_think_time(20);


	lr_start_transaction("UC02_TR07_test_start");


	lr_think_time(17);

	web_custom_request("updateOrderSteps", 
		"URL=https://loadtest.uxcrowd.ru/api/v2/customer/updateOrderSteps", 
		"Method=PUT", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/order?id={orderId}", 
		"Snapshot=t101.inf", 
		"Mode=HTML", 
		"EncType=application/json;charset=UTF-8", 
		"Body={\"orderId\":{orderId},\"steps\":[{\"question\":\"qwerty{intro_num}?\",\"linkList\":[],\"stepType\":\"TEXT\",\"orderNum\":0}],\"metrics\":[]}", 
		LAST);

	web_url("calculatePrice", 
		"URL=https://loadtest.uxcrowd.ru/api/customer/calculatePrice?orderId={orderId}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/order?id={orderId}", 
		"Snapshot=t102.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC02_TR07_test_start",LR_AUTO);

	lr_think_time(22);


	lr_start_transaction("UC02_TR08_start_free_test");


	lr_think_time(18);

	web_custom_request("orderFreeInit", 
		"URL=https://loadtest.uxcrowd.ru/api/v2/customer/orderFreeInit", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/order?id={orderId}", 
		"Snapshot=t103.inf", 
		"Mode=HTML", 
		"EncType=application/json;charset=UTF-8", 
		"Body={\"orderId\":{orderId}}", 
		LAST);


	lr_end_transaction("UC02_TR08_start_free_test",LR_AUTO);

	lr_think_time(40);

	lr_start_transaction("UC02_TR09_back_to_test_list");


	lr_think_time(7);

	web_url("list-orders_2", 
		"URL=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/order?id={orderId}", 
		"Snapshot=t104.inf", 
		"Mode=HTML", 
		LAST);

	web_url("account_3", 
		"URL=https://loadtest.uxcrowd.ru/api/account", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"Snapshot=t105.inf", 
		"Mode=HTML", 
		LAST);

	web_url("user_3", 
		"URL=https://loadtest.uxcrowd.ru/api/v2/tariff/user", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"Snapshot=t110.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("orders_2", 
		"URL=https://loadtest.uxcrowd.ru/api/v3/customer/orders", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"Snapshot=t112.inf", 
		"Mode=HTML", 
		"EncType=application/json;charset=UTF-8", 
		"Body={\"direction\":\"DESC\",\"filter\":[\"ACTIVE\",\"COMPLETED\",\"DRAFT\",\"WAIT_CONFIRMATION\"],\"page\":0,\"size\":10,\"sort\":[\"startDate\"]}", 
		LAST);


	lr_think_time(6);


	lr_end_transaction("UC02_TR09_back_to_test_list",LR_AUTO);

	lr_start_transaction("UC02_TR10_logout");


	web_custom_request("logout", 
		"URL=https://loadtest.uxcrowd.ru/api/logout", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"Snapshot=t117.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);


	web_url("loadtest.uxcrowd.ru_3", 
		"URL=https://loadtest.uxcrowd.ru/", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t121.inf", 
		"Mode=HTML", 
		LAST);


	lr_end_transaction("UC02_TR10_logout",LR_AUTO);


	lr_think_time(19);

	lr_think_time(10);

	return 0;
}