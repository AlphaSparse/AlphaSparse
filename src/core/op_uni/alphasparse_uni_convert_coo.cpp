#include "alphasparse/spapi.h"
#ifdef __DCU__
#include "alphasparse_dcu.h"
#endif
#include "alphasparse/format.h"
#include "alphasparse/spmat.h"

alphasparse_status_t ONAME(
    const alphasparse_matrix_t source,       /* convert original matrix to CSC representation */
    const alphasparse_operation_t operation, /* as is, transposed or conjugate transposed */
    alphasparse_matrix_t *dest) {

    alphasparse_status_t status =  alphasparse_convert_coo(source, operation, dest);

    if(source->exe != ALPHA_SPARSE_EXE_HOST)
    {
#ifdef __DCU__
#ifdef S
    host2device_s_coo((alphasparse_matrix_t)dest);
#endif
#ifdef D
    host2device_d_coo((alphasparse_matrix_t)dest);
#endif
#ifdef C
    host2device_c_coo((alphasparse_matrix_t)dest);
#endif
#ifdef Z
    host2device_z_coo((alphasparse_matrix_t)dest);
#endif
#endif
        return status;
    }
    else
        return status;
}