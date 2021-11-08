using System;
using System.IO;
using System.Text;

/*
 * Copyright (c) 2017, Adam <Adam@sigterm.info>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
namespace net.runelite.cache.script.assembler
{
	using ScriptDefinition = net.runelite.cache.definitions.ScriptDefinition;
	using Instructions = net.runelite.cache.script.Instructions;
	using ProgContext = net.runelite.cache.script.assembler.rs2asmParser.ProgContext;
	using ANTLRInputStream = org.antlr.v4.runtime.ANTLRInputStream;
	using CommonTokenStream = org.antlr.v4.runtime.CommonTokenStream;
	using ParseTreeWalker = org.antlr.v4.runtime.tree.ParseTreeWalker;

	public class Assembler
	{
		private readonly Instructions instructions;

		public Assembler(Instructions instructions)
		{
			this.instructions = instructions;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public net.runelite.cache.definitions.ScriptDefinition assemble(java.io.InputStream in) throws java.io.IOException
		public virtual ScriptDefinition assemble(Stream @in)
		{
			// Get our lexer
			rs2asmLexer lexer = new rs2asmLexer(new ANTLRInputStream(new StreamReader(@in, Encoding.UTF8)));

			LexerErrorListener errorListener = new LexerErrorListener();
			lexer.addErrorListener(errorListener);

			// Get a list of matched tokens
			CommonTokenStream tokens = new CommonTokenStream(lexer);

			// Pass the tokens to the parser
			rs2asmParser parser = new rs2asmParser(tokens);

			// Specify our entry point
			ProgContext progContext = parser.prog();

			if (errorListener.Errors > 0)
			{
				throw new Exception("syntax error");
			}

			// Walk it and attach our listener
			ParseTreeWalker walker = new ParseTreeWalker();

			// walk through first and resolve labels
			LabelVisitor labelVisitor = new LabelVisitor();
			walker.walk(labelVisitor, progContext);

			ScriptWriter listener = new ScriptWriter(instructions, labelVisitor);
			walker.walk(listener, progContext);

			return listener.buildScript();
		}
	}

}