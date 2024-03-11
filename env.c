
void	prova()
{
	while (envp[j][i])
	{
		if (!strchr(envp[j], '='))
		{
			utils.key = strdup(envp[j]);
		}
	}
}