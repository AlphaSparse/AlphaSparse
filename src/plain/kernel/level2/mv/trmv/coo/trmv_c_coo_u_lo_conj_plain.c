#include "alphasparse/kernel_plain.h"
#include "alphasparse/util.h"

alphasparse_status_t
ONAME(const ALPHA_Number alpha,
                            const ALPHA_SPMAT_COO *A,
                            const ALPHA_Number *x,
                            const ALPHA_Number beta,
                            ALPHA_Number *y)
{
    const ALPHA_INT m = A->rows;
	const ALPHA_INT n = A->cols;
	if(m != n) return ALPHA_SPARSE_STATUS_INVALID_VALUE;

	const ALPHA_INT nnz = A->nnz;
	for(int i = 0; i < m; ++i)
	{  
		alpha_mule(y[i], beta);
		alpha_madde(y[i], alpha, x[i]);
	}
    for(ALPHA_INT i = 0; i < nnz; ++i)
    {  
		const ALPHA_INT r = A->row_indx[i];
		const ALPHA_INT c = A->col_indx[i];
		if(r > c)
	 	{
			ALPHA_Number v;
			cmp_conj(v, A->values[i]);
			alpha_mule(v, x[r]);
			alpha_madde(y[c], alpha, v);
		} 
    }

	return ALPHA_SPARSE_STATUS_SUCCESS;
}