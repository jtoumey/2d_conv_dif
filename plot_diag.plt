reset
set key left top
plot "phi_diag_uds.dat" using 1:2 w lp title "uds", "phi_diag_cds.dat" using 1:2 w lp title "cds"
