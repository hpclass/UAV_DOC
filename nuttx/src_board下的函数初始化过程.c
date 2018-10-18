nsh_main()
  -> nsh_initialize()
     ->  (void)nsh_romfsetc();
     ->  (void)boardctl(BOARDIOC_INIT, 0);
     	-> board_app_initialize() //src/board/px4fmu_init.c
     -> ret = nsh_consolemain(0, NULL);
