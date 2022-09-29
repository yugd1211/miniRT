#include <stdio.h>
#include <stdlib.h>

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

char	**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int	check(char *sep, char c)
{
	int	i;

	i = 0;
	while (sep[i] != '\0')
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	str_num(char const *str, char *charset, int *save)
{
	int	i;
	int	j;
	int	ch_switch;
	int	num;

	i = 0;
	ch_switch = 1;
	num = 0;
	while (str[i] != '\0')
	{
		if (ch_switch == 1 && check(charset, str[i]) == 0)
		{
			j = i;
			while (check(charset, str[j]) != 1 && str[j++] != '\0')
				save[num]++;
			num++;
		}
		if (check(charset, str[i++]) == 1)
			ch_switch = 1;
		else
			ch_switch = 0;
	}
	return (num);
}

void	str_save(char const *str, char *charset, char **save_str)
{
	int		i;
	int		j;
	int		k;
	int		ch_switch;
	int		num;

	i = 0;
	num = 0;
	ch_switch = 1;
	while (str[i] != '\0')
	{
		if (ch_switch == 1 && check(charset, str[i]) == 0)
		{
			j = i;
			k = 0;
			while (check(charset, str[j]) != 1 && str[j] != '\0')
				save_str[num][k++] = str[j++];
			save_str[num++][k] = '\0';
		}
		if (check(charset, str[i++]) == 1)
			ch_switch = 1;
		else
			ch_switch = 0;
	}
}

char	**ft_split(char const *str, char *charset, int *save_num)
{
	char	**save_str;
	int		save[10000];
	int		i;
	int		num;

	i = 0;
	while (i < 10000)
		save[i++] = 0;
	num = str_num(str, charset, save);
	*save_num = num;
	save_str = (char **)malloc((num + 1) * sizeof(char *));
	if (!(save_str))
		return (NULL);
	save_str[num] = 0;
	i = 0;
	while (i < num)
	{
		save_str[i] = (char *)malloc((save[i] + 1) * sizeof(char));
		if (!save_str[i])
			return (ft_malloc_error(save_str));
		i++;
	}
	str_save(str, charset, save_str);
	return (save_str);
}

int	num_th_power_of_ten(size_t num)
{
	size_t	dec;
	size_t	count;

	dec = 1;
	count = 0;
	while (count < num)
	{
		dec *= 10;
		count++;
	}
	return (dec);
}

double	ft_atof(char *str)
{
	double	num;
	size_t	dec_point_num;
	int		i;
	int		sign;

	num = 0;
	dec_point_num = 0;
	i = 0;
	sign = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while ('0' <= str[i] && str[i] <= '9')
		num = num * 10 + str[i++] - '0';
	if (str[i++] == '.')
		while ('0' <= str[i] && str[i] <= '9')
		{
			num = num * 10 + str[i++] - '0';
			dec_point_num++;
		}
	num = num / num_th_power_of_ten(dec_point_num);
	return (num * sign);
}

// int	main(void)
// {
// 	char	**temp;
// 	char	*str = "hello this point	is 		1,2,3, ,5";
// 	int		count;
// 	int		i;

// 	i = 0;
// 	count = 0;
// 	printf("10 : %lf -10.1234 : %lf  -0.1235425 : %lf 0.0001 : %lf\n", ft_atof("10"), ft_atof("-10.1234"), ft_atof(" -0.1235425"), ft_atof("0.0001"));
// 	temp = ft_split(str, " \t,", &count);
// 	while (i < count)
// 		printf("%s %d\n", temp[i++], count);
// 	return (0);
// }

int	ft_rounding(double num)
{
	int	round_down;

	round_down = (int)num;
	if (num - (double)round_down >= 0.50000000)
		return (round_down + 1);
	return (round_down);
}

int main(void)
{
	t_point point1;
	t_point	point2;
	int		color;

	color = 255 << 16 | 255 << 8 | 255;
	point1.x = 1.5;
	point1.y = 2.4;
	point1.z = 3.75;
	point2 = point1;
	printf("p2.x: %lf p2.y : %x p2.z : %lf\n", point2.x, color, point2.z);
	return (0);
}