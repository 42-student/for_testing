/*
* {[-_-]}
*/

#include <stdio.h>

size_t	ft_strlen(const char *s) {
	size_t i = 0;
	while (s[i]) {
		i++;
	}

	return i;
}

int	ft_check_char(char *str) {
	while (*str) {
		if ((*str >= 9 && *str <= 13) || (*str == ' ') || (*str == '-') || (*str == '+')) {
			return 0;
		} else {
			str++;
		}
	}

	return 1;
}

int	ft_check_base(char *base) {
	int i = 0;
	while (base[i] && base[i + 1] != '\0' && ft_check_char(base)) {
		int j = i + 1;
		while (base[j]) {
			if (base[i] == base[j]) {
				return -1;
			}
			j++;
		}
		i++;
	}

	return (i + 1);
}

int	ft_assign_sign(char *str, int *i) {
	int sign = 0;
	while (str[*i] && (str[*i] == '-' || str[*i] == '+')) {
		if (str[*i] == '-') {
			sign++;
		}
		(*i)++;
	}

	if (sign % 2 == 0) {
		return 1;
	} else {
		return -1;
	}
}

int	ft_find_ichar(char c, char *base) {
	int i = 0;
	while (base[i]) {
		if (c == base[i]) {
			return i;
		}
		i++;
	}

	return -1;
}

int	ft_extract_number(char *str, char *base, size_t int_base) {
	int res = 0;
	int i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <=13) || str[i] == 32)) {
		i++;
	}

	int sign = ft_assign_sign(str, &i);
	while (str[i] && (str[i] >= 33 && str[i] <= 126)) {
		int i_char = ft_find_ichar(str[i], base);
		if (i_char == -1) {
			return 0;
		}
		res = res * int_base + i_char;
		i++;
	}

	return (res * sign);
}

int	ft_atoi_base(char *str, char *base) {
	if (str == NULL || base == NULL) {
		return 0;
	}

	int int_base = ft_check_base(base);
	if (int_base != ft_strlen(base) || int_base <= 1) {
		return 0;
	}

	int number = ft_extract_number(str, base, int_base);
	if (number == 0) {
		return 0;
	}

	return number;
}

////////////////// MAIN

int	main(int ac, char **av) {
	int result = 0;
	if (ac == 3) {
		result = ft_atoi_base(av[1], av[2]);
	} else {
		printf("Error! Usage './a.out <nbr_str> <base_str>'\n");
	}
	printf("The result is: %d\n", result);

	return 0;
}

