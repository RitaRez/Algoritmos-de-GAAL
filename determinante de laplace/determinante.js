//Fiz em js pq a em c OBVIAMENTE da segfault

function determinante(mat){
    
    if(mat.length != mat[0].length){
        console.log('A matriz não possui determinante');
        return -1;
    }
    var ordem = mat.length,
    det = 0;

    if(ordem == 1)
        return mat[0][0];
    if (ordem == 2) 
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    else 
        for (var j = 0; j < ordem; j++) 
            det += mat[0][j] * cofator(mat, 0, j);
    
    return det;        
}


function cofator(mat, linha, coluna){
    var submat = [], 
    ordem = mat.length, 
    m = 0;

    for (var i = 1; i < ordem; i++) {
        submat[m] = [];

        for (var j = 0; j < ordem; j++) {
            if (j !== coluna) {
                submat[m].push(mat[i][j]);
            }
        }
        m++;
    }
    return (coluna % 2 ? -1 : 1) * determinante(submat);
}


determinante([
    [2, 1, 2, 3, 4, 5, 6, 7, 2, 3],
    [0, 2, 0, 0, 0, 0, 0, 2, 3, 2],
    [0, 0, 4, 5, 5, 5, 2, 3, 2, 1],
    [0, 0, 0, 2, 0, 2, 3, 2, 5, 2],
    [0, 0, 0, 0, 4, 3, 2, 0, 5, 3],
    [0, 0, 0, 0, 0, 1, 0, 0, 5, 4],
    [0, 0, 0, 0, 0, 0, 4, 0, 5, 5],
    [0, 0, 0, 0, 0, 0, 0, 2, 5, 6],
    [0, 0, 0, 0, 0, 0, 0, 0, 1, 7],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 2]
])