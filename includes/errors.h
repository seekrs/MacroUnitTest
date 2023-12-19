/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:38:06 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 16:38:12 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_UT_ERRORS__
#define __MLX_UT_ERRORS__

#include <pch.h>

enum class e_kind
{
	message,
	warning,
	error,
	fatal_error
};

namespace mlxut::core::error
{
	void report(e_kind kind, std::string msg, ...);
}

#endif // __MLX_ERRORS__
