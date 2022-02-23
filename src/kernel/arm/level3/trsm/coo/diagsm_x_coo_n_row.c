#include "alphasparse/kernel.h"
#include "alphasparse/util.h"
#include "alphasparse/opt.h"
#include <memory.h>

alphasparse_status_t ONAME(const ALPHA_Number alpha, const ALPHA_SPMAT_COO *A, const ALPHA_Number *x, const ALPHA_INT columns, const ALPHA_INT ldx, ALPHA_Number *y, const ALPHA_INT ldy)
{
    ALPHA_Number diag[A->rows];

    memset(diag, '\0', A->rows * sizeof(ALPHA_Number));
    int num_thread = alpha_get_thread_num(); 

#ifdef _OPENMP
#pragma omp parallel for num_threads(num_thread)
#endif
    for (ALPHA_INT r = 0; r < A->nnz; r++)
    {
        if(A->row_indx[r] == A->col_indx[r])
        {
            diag[A->row_indx[r]] = A->values[r];
        }
    }

#ifdef _OPENMP
#pragma omp parallel for num_threads(num_thread)
#endif    
    for (ALPHA_INT r = 0; r < A->rows; ++r)
    {
        for (ALPHA_INT c = 0; c < columns; ++c)
        {
            ALPHA_Number t;
            alpha_mul(t, alpha, x[index2(r, c, ldx)]);
            alpha_div(y[index2(r, c, ldy)], t, diag[r]);
        }
    }
    return ALPHA_SPARSE_STATUS_SUCCESS;
}