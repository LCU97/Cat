# 🎮 H.W.H


| 언리얼 기반 액션 RPG 게임 프로젝트
---

<p align="center">
  <img src="https://github.com/user-attachments/assets/6ecc5318-cf88-43e0-8b23-16405cb3764d" width="800"/>
</p>


<br>

## 이철의

## 📋 목차
<a id="top"></a>

1. [📖 프로젝트 목표](#-프로젝트-목표)
2. [🎉 성과](#-성과)
3. [🧠 주요 시스템 구현 및 아키텍처](#-주요-시스템-구현-및-아키텍처)
   - InputSystem
   - FSM && Weapon
   - Targeting
4. [⚙️ 기술 스택](#-기술-스택)


---

<br>

## 📖 프로젝트 목표
확장성과 유지보수성를 고려한 캐릭터 시스템 프레임워크 구축. 조작감이 뛰어난 액션 게임의 기반 설계

---

<br>

## 🎉 성과

<br>

- 상태와 능력을 객체화하고 Component 로 관리하도록 설계하여 캐릭터 코드의 책임을 나누고 기능 확장이 쉬운 구조 구현
- Command Pattern 기반 입력 시스템을 구현하여 입력 처리와 Character 행동 로직을 분리
- Data Asset을 활용해 무기 능력과 상태 값을 디자이너가 직접 조정할 수 있도록 제작


<br>
 
<table align="center">
<tr>
<td rowspan="2">
<img src="https://github.com/user-attachments/assets/5cfd90c7-576e-40f7-b9f2-20bcb514eb64" width="450">
</td>

<td>
<img src="https://github.com/user-attachments/assets/e6832b98-c517-4c86-a5b4-04bbc91768d1" width="350">
</td>
</tr>

<tr>
<td>
<img src="https://github.com/user-attachments/assets/eef924b8-1e4b-45cf-aa44-3e824f942251" width="350">
</td>
</tr>
</table>


---

<br>

## 🧠 주요 시스템 구현 및 아키텍처


## 📄 InputSystem

설계 목표 : 

- Command 패턴을 적용해 입력과 실제 동작을 분리. Invoker 가 실제 동작에 관여하지 않도록하여 커맨드의 Excute 시 실제 동작이 독립적으로 실행되도록 설계.
- 매번 InputHandler 의 객체를 생성하지 않고도 프로퍼티 창에서 커스텀 클래스를 생성.
- InputBuffer 를 통해 애니메이션 도중 들어온 입력을 기억했다가 다음 동작을 매끄럽게 연결하여 부드러운 조작감 확보.

<br>

### 핵심 코드 <br>
### 1. <br>
InputBuffer 및 InputHandler 생성 관리. `DuplicateObject` 로 에디터에서 커스텀 되어 있는 InputHandler 복제 <br>
[<코드 확인>](https://github.com/LCU97/Cat/blob/af7f21bcaf3acc807eb1b1c9f41567732fd567f5/Source/HumanAndCat/Private/Inputs/ANS_BufferInput.cpp#L12) <br>

`MakeBuffer` 매크로로 `InputComponent` 에서 `InputBufferObject` 생성 및 `InputHandler` 와 공유 [<코드 확인>](https://github.com/LCU97/Cat/blob/74f4049f9e714a675f13adf7c79a5690b7ae8078/Source/HumanAndCat/Private/Inputs/InputComponent/InputManagerComponent.cpp#L71)
<img width="1611" height="419" alt="image" src="https://github.com/user-attachments/assets/f3c11ea5-65ef-40e2-a58c-4b5574f194c8" />

<br>

### 2. <br>
`InputHandler` 를 사용하는데에 'EditInlineNew' 와 'Instanced' 지정자를 적용하여 에디터에서 별도의 InputHanlder 생성없이 인스턴스를 만들고 복사 생성. [<코드 확인>](https://github.com/LCU97/Cat/blob/1b4d7c6e9cd0bb5d9f85fc9da4816e56dc94436d/Source/HumanAndCat/Public/Inputs/Handlers/InputHandler.h#L26)
<img width="941" height="701" alt="image" src="https://github.com/user-attachments/assets/fe2dcb07-fd34-40d9-b22a-546405c3c8f1" /> <br>

`InputHandler` 에서 `InputBuffer` 를 프로퍼티에 맞게 관리 및 처리 `InputCommand` 를 생성하여 Excute. <br>
[<코드 확인>](https://github.com/LCU97/Cat/blob/main/Source/HumanAndCat/Private/Inputs/Handlers/InputHandler.cpp) <br>

<br>

### 3. <br>
`BaseCommad` 의 공통 가상 메서드 `ActionExecute`를 `override` 하여 각 Command 가 독립적인 액션 동작 실행 <br>
[<코드 확인>](https://github.com/LCU97/Cat/blob/1b4d7c6e9cd0bb5d9f85fc9da4816e56dc94436d/Source/HumanAndCat/Private/Inputs/InputCommand/AttackStateCommand.cpp#L20) <br>

<br>

## ⚔ FSM && Weapon

입력 시스템은 클래스 다이어그램을 약간 아키텍처 형식으로 만들어서 넣어줘야할듯

fsm 쪽은 코드 설명과 링크만 넣어도 될듯

<br>

## 🎯 Targeting

코드 설명 및 어떤식으로 구현한건지를 꼭 설명할것

<br>

---

## ⚙️ 기술 스택

---
