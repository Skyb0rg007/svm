
let c_gnu = 1
let c_no_c11 = 0

let g:ale_c_gcc_options = '-Wall -Wextra -std=c11 -pedantic'
let &path = ''
function! AddToInclude(dir)
    let g:ale_c_gcc_options .= ' -I' . a:dir
    let &path .= ',' . a:dir
endfunction

call AddToInclude('/usr/include')
call AddToInclude('/usr/lib/gcc/x86_64-redhat-linux/10/include')
call AddToInclude(expand('<sfile>:p:h') . '/include')

augroup svm
    autocmd BufRead,BufNewFile *.h set ft=c
augroup end
