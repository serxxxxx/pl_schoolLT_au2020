vuser_end()
{  
	lr_start_transaction("VTS_disconnect");

	lrvtc_disconnect();
	
	lr_end_transaction("VTS_disconnect", LR_AUTO);

	return 0;
}
