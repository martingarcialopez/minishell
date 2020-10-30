#include "../includes/builtins.h"
#include "../includes/libft.h"

int main(int v, char **n, char **envp)
{
	int	i;
	char	*line;

	if (n != 0)
	{} //error
	init_env(envp);
	i = 1;
	while(n)
	{
		ft_printf("(los voltereta)-> ");
		i = gnl(0, &line);
		//do whatever with line
		free(line);
	}
}
