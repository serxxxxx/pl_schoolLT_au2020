UC05_whatching_video()
{	
	//получаем логин клиента и id теста
	lrvtc_retrieve_message("Email_client_execute");
	lrvtc_retrieve_message("Order_id_execute");	
	
	web_reg_save_param_ex(
	    "ParamName=token", 
	    "LB/IC=Set-Cookie: XSRF-TOKEN=",
	    "RB/IC=;",
		LAST
	);

	web_url("loadtest.uxcrowd.ru", 
		"URL=https://loadtest.uxcrowd.ru/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/api/account", ENDITEM,
		LAST);

	web_url("ru.json", 
		"URL=https://loadtest.uxcrowd.ru/assets/lang/ru.json", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("X-XSRF-TOKEN", 
		"{token}");

	web_url("headerGreenWhite.html", 
		"URL=https://loadtest.uxcrowd.ru/tmpl/tmpl_landing_new/headerGreenWhite.html", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	web_url("home.html", 
		"URL=https://loadtest.uxcrowd.ru/tmpl/tmpl_landing_new/home.html", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);

	web_url("footer.html", 
		"URL=https://loadtest.uxcrowd.ru/tmpl/tmpl_landing_new/footer.html", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	web_url("ux-logo-new-white.svg", 
		"URL=https://loadtest.uxcrowd.ru/", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t6.inf", 
		"Mode=HTML",
		LAST);

	lr_start_transaction("UC05_TR01_login");

	web_url("modal-login.html", 
		"URL=https://loadtest.uxcrowd.ru/tmpl/tmpl_home/modal-login.html", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);
	
	web_reg_save_param_regexp (
	    "ParamName=token2",
	    "RegExp=Set-Cookie: XSRF-TOKEN=(.*?);",
	    "Ordinal=2",
		LAST
	);
	
	web_submit_data("authentication", 
		"Action=https://loadtest.uxcrowd.ru/api/authentication", 
		"Method=POST", 
		"TargetFrame=", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		"EncodeAtSign=YES", 
		ITEMDATA, 
		"Name=username", "Value={Email_client_execute}", ENDITEM, 
		"Name=password", "Value=ajbPwV", ENDITEM, 
		"Name=remember-me", "Value=undefined", ENDITEM, 
		"Name=submit", "Value=Login", ENDITEM, 
		LAST
	);

	web_add_header("X-XSRF-TOKEN", 
		"{token2}");

	web_url("account", 
		"URL=https://loadtest.uxcrowd.ru/api/account", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		LAST);

	web_url("list-orders", 
		"URL=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://loadtest.uxcrowd.ru/", 
		"Snapshot=t12.inf", 
		"Mode=HTML",
		LAST);

	web_url("main_template.html", 
		"URL=https://loadtest.uxcrowd.ru/tmpl/tmpl_customer/main_template.html", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"Snapshot=t16.inf", 
		"Mode=HTML", 
		LAST);

	web_url("header.html", 
		"URL=https://loadtest.uxcrowd.ru/tmpl/tmpl_customer/header.html", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"Snapshot=t18.inf", 
		"Mode=HTML", 
		LAST);

	web_url("new.video.html", 
		"URL=https://loadtest.uxcrowd.ru/tmpl/tmpl_customer/new.video.html", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"Snapshot=t19.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("X-XSRF-TOKEN", 
		"{token2}");

	web_url("user", 
		"URL=https://loadtest.uxcrowd.ru/api/v2/tariff/user", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"Snapshot=t21.inf", 
		"Mode=HTML",
		LAST);

	web_custom_request("orders", 
		"URL=https://loadtest.uxcrowd.ru/api/v3/customer/orders", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/list-orders", 
		"Snapshot=t22.inf", 
		"Mode=HTML", 
		"EncType=application/json;charset=UTF-8", 
		"Body={\"direction\":\"DESC\",\"filter\":[\"ACTIVE\",\"COMPLETED\",\"DRAFT\",\"WAIT_CONFIRMATION\"],\"page\":0,\"size\":10,\"sort\":[\"startDate\"]}", 
		LAST);

	lr_end_transaction("UC05_TR01_login",LR_AUTO);

	lr_start_transaction("UC05_TR02_test_page_open");

	web_reg_save_param_regexp (
	    "ParamName=videoID",
	    "RegExp=videoId\":\"(.*?)\"",
	    "Ordinal=1",
		LAST
	);
	
	// везде OrderID заменил на Order_id_execute
	web_url("{Order_id_execute}", 
		"URL=https://loadtest.uxcrowd.ru/api/v3/customer/order/{Order_id_execute}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/tests/{Order_id_execute}", 
		"Snapshot=t26.inf", 
		"Mode=HTML", 
		LAST);

	web_url("get-tester_task_link", 
		"URL=https://loadtest.uxcrowd.ru/api/server/get-tester_task_link?customerOrderId={Order_id_execute}&targetType=SITE", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/tests/{Order_id_execute}", 
		"Snapshot=t28.inf", 
		"Mode=HTML",
		LAST);

	lr_end_transaction("UC05_TR02_test_page_open",LR_AUTO);

	lr_start_transaction("UC05_TR03_test_video_open");

	web_url("user_3", 
		"URL=https://loadtest.uxcrowd.ru/api/v2/tariff/user", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/new-video/{videoID}", 
		"Snapshot=t29.inf", 
		"Mode=HTML",
		LAST);

	web_url("relatedVideoIds", 
		"URL=https://loadtest.uxcrowd.ru/api/video/relatedVideoIds?videoId={videoID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/new-video/{videoID}", 
		"Snapshot=t30.inf", 
		"Mode=HTML", 
		LAST);
		
	web_reg_save_param_ex(
		"ParamName=fileName", 
		"LB/IC=fileName\":\"",
		"RB/IC=.webm",
		LAST
	);	
	
	web_url("{videoID}", 
		"URL=https://loadtest.uxcrowd.ru/api/v3/video/{videoID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/new-video/{videoID}", 
		"Snapshot=t31.inf", 
		"Mode=HTML", 
		LAST);

	web_url("tags", 
		"URL=https://loadtest.uxcrowd.ru/api/v3/video/{videoID}/tags", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/new-video/{videoID}", 
		"Snapshot=t33.inf", 
		"Mode=HTML",
		LAST);

	web_url("notes", 
		"URL=https://loadtest.uxcrowd.ru/api/v3/video/{videoID}/notes", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/new-video/{videoID}", 
		"Snapshot=t34.inf", 
		"Mode=HTML",
		LAST);

	web_stream_open("ID=1", "URL=https://loadtest.uxcrowd.ru/videos/{fileName}.mp4", "Protocol=HTTP", LAST);

	/*Basic streaming flow skeleton:
	//Play the movie from the beginning(the entire movie duration is XXX)
	web_stream_play("ID=1", "PlayingDuration=XXX", LAST);
	//Pause the movie
	web_stream_pause("ID=1","PausingDuration=XXX",LAST);
	//Stop the movie
	web_stream_stop("ID=1",LAST);*/
	
	lr_end_transaction("UC05_TR03_test_video_open",LR_AUTO);
	
	lr_start_transaction("UC05_TR04_test_video_play");
	
	web_stream_play("ID=1", "PlayingDuration=10", LAST);
	
	lr_end_transaction("UC05_TR04_test_video_play",LR_AUTO);	
	
	lr_start_transaction("UC05_TR05_test_video_stop");
	
	web_stream_stop("ID=1",LAST);

	lr_end_transaction("UC05_TR05_test_video_stop",LR_AUTO);	

	web_stream_close("ID=1", LAST);
	
	lr_start_transaction("UC05_TR06_logout");
	
	web_custom_request("logout", 
		"URL=https://loadtest.uxcrowd.ru/api/logout", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://loadtest.uxcrowd.ru/app-customer-home/new-video/{videoID}", 
		"Snapshot=t35.inf", 
		"Mode=HTML", 
		"EncType=",
		LAST
	);
	
	
	lr_end_transaction("UC05_TR06_logout",LR_AUTO);

	return 0;
}