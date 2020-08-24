vuser_init()
{		lr_start_transaction("VTS_Connect");
		

	  lr_end_transaction("VTS_Connect", LR_AUTO);

	return 0;
}
