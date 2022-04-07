﻿//---------------------------------------------------------------------------------------------------------
//	Copyright © 2007 - 2021 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class is used to replace some calls to the java.lang.Math class.
//---------------------------------------------------------------------------------------------------------
using System;

internal static class MathHelper
{
	private static Random randomInstance = null;

	public static double NextDouble
	{
		get
		{
			if (randomInstance == null)
				randomInstance = new Random();

			return randomInstance.NextDouble();
		}
	}

	public static double Expm1(double x)
	{
		if (Math.Abs(x) < 1e-5)
			return x + 0.5 * x * x;
		else
			return Math.Exp(x) - 1.0;
	}

	public static double Log1p(double x)
	{
		double y = x;
		return ((1 + y) == 1) ? y : y * (Math.Log(1 + y) / ((1 + y) - 1));
	}
}