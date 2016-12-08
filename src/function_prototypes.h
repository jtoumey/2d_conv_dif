// Hannah Montana
// Declarations of function prototypes
void read_input(struct block *grid_data, struct properties *phys_prop, struct settings *solv_setting);
void calc_grid(struct block *grid_data, struct cell *cell_data);
void initialize_properties(struct block *grid_data, struct cell *cell_data, struct properties *phys_prop, float *phi_prev, float *S_u_correct);
void calc_fvm_coeff(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop);
void set_boundary_conditions(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data, struct properties *phys_prop);
void solve_jacobi(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data);
void calc_residual(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data, float *resid, float *frp);
void write_results(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data);
void calc_correction(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data, struct properties *phys_prop, float *phi_prev, float *S_u_correct);
// Debug
void write_coefficients(struct block *grid_data, struct coeff *fvm_coeff);
