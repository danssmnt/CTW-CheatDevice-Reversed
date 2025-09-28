# Contributing to the Project

This project is completely open for anyone to contribute and help, and there are many ways to contribute to it:

 - Help fully Reverse Engineer this plugin
 - Make pull requests for cleaning code / improving binary accuracy...
 - Create issues when something unexpected with the compiled build happens (make sure it hasn't been created by other people first)
 - Spread this project to Forums, Reddit, Discord Servers, etc.
 - Make your own versions of this Cheat Device (giving credit to the original author and other contributors)

## Code Styling

Just try to follow what is already there, we aren't very strict about it though (I too find sticking to a code styling very difficult), but, the closer to what qwikrazor87 would've written, the better.

## Reverse Engineering

> [!NOTE]
> This project was made with Ghidra, but you can also use IDA Pro if you want, but keep in mind if you do it you're on your own. I don't know how to use IDA. The rest of this section will be about Ghidra.

> [!IMPORTANT]
> It is recommended you have already some experience with Ghidra and low-level code and debugging. Otherwise you probably won't be able to get too far.

1. Download the original plugin. You can find it [here](https://github.com/danssmnt/CTW-CheatDevice-Reversed/releases).
2. Download / Install Ghidra (You should already have it). You can find it [here](https://github.com/NationalSecurityAgency/ghidra/releases).
3. Setup your Ghidra for PSP Reverse Engineering, here's a [guide](https://psp-re.github.io/quickstart/).
4. Create a new local project on your PC and inside it put the ``.prx`` file.
5. Follow the instructions on the mentioned guide (use ``pspsdk.gdt``).
7. Start reversing! You can use this project as a reference if needed.