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
4. [블로그 개발 기록](#개발-기록)
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
- 타겟팅 시 부드러운 카메라 움직임 구현


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

<img width="1085" height="859" alt="InputSystem drawio (1)" src="https://github.com/user-attachments/assets/a4982b0c-1fe8-4d4d-a792-2418256db6a6" />

<br>

### 핵심 코드 <br>
### 1. AnimNotifyState && InputComponent <br>
InputBuffer 및 InputHandler 생성 관리. `DuplicateObject` 로 에디터에서 커스텀 되어 있는 InputHandler 복제 <br>
[<코드 확인>](https://github.com/LCU97/Cat/blob/af7f21bcaf3acc807eb1b1c9f41567732fd567f5/Source/HumanAndCat/Private/Inputs/ANS_BufferInput.cpp#L12) <br>

`MakeBuffer` 매크로로 `InputComponent` 에서 `InputBufferObject` 생성 및 `InputHandler` 와 공유 [<코드 확인>](https://github.com/LCU97/Cat/blob/74f4049f9e714a675f13adf7c79a5690b7ae8078/Source/HumanAndCat/Private/Inputs/InputComponent/InputManagerComponent.cpp#L71)
<img width="1611" height="419" alt="image" src="https://github.com/user-attachments/assets/f3c11ea5-65ef-40e2-a58c-4b5574f194c8" />

<br>

### 2. InputHandler <br>
`InputHandler` 를 사용하는데에 'EditInlineNew' 와 'Instanced' 지정자를 적용하여 에디터에서 별도의 InputHanlder 생성없이 인스턴스를 만들고 복사 생성. [<코드 확인>](https://github.com/LCU97/Cat/blob/1b4d7c6e9cd0bb5d9f85fc9da4816e56dc94436d/Source/HumanAndCat/Public/Inputs/Handlers/InputHandler.h#L26)
<img width="941" height="701" alt="image" src="https://github.com/user-attachments/assets/fe2dcb07-fd34-40d9-b22a-546405c3c8f1" /> <br>

`InputHandler` 에서 `InputBuffer` 를 프로퍼티에 맞게 관리 및 처리 `InputCommand` 를 생성하여 Excute. <br>
[<코드 확인>](https://github.com/LCU97/Cat/blob/main/Source/HumanAndCat/Private/Inputs/Handlers/InputHandler.cpp) <br>

<br>

### 3. InputCommand <br>
`BaseCommad` 의 공통 가상 메서드 `ActionExecute`를 `override` 하여 각 Command 가 독립적인 액션 동작 실행 <br>
[<코드 확인>](https://github.com/LCU97/Cat/blob/1b4d7c6e9cd0bb5d9f85fc9da4816e56dc94436d/Source/HumanAndCat/Private/Inputs/InputCommand/AttackStateCommand.cpp#L20) <br>

<br>

## ⚔ FSM && Weapon

설계 목표 :

- 캐릭터가 사용하는 State와 Ability 를 Enum 으로 사용 시 캐릭터의 책임과 코드 복잡도가 높아져 유지보수 및 기능 추가가 어려워짐
  이를 해결하기 위해 State 패턴을 사용하여 상태를 객체화하여 확장성을 확보
- State 객체를 StateManagerComponent 가 관리하도록 설계하여 캐릭터 클래스가 상태 로직에 직접 의존하지 않도록 구조를 분리
- 실제 행동 로직을 Ability 로 State 와 분리하여 상태 수 증가 방지 및 상태는 여러 무기에서 실제 행동(Ability)은 여러 상태에서 설정 가능하도록 설계
  
<br>

### 핵심 코드 <br>

### 1.StateObject && StateComponent <br>
- [BaseStateObject](https://github.com/LCU97/Cat/blob/main/Source/HumanAndCat/Private/Objects/BaseStateObject.cpp)를 기반으로 상태 클래스를 구현 <br>
- [StateManagerComponent](https://github.com/LCU97/Cat/blob/main/Source/HumanAndCat/Private/Components/BaseStateManagerComponent.cpp) 에서 공통 메서드를 호출하면 각 상태 클래스에서 `virtual` 메서드를 `override`하여 상태별 로직을 실행

<br>

### 2. AbilityObject && AbilityComponent <br>
- [BaseAbilityObject](https://github.com/LCU97/Cat/blob/main/Source/HumanAndCat/Private/Objects/BaseAbilityObject.cpp) 를 기반으로 능력 클래스를 구현 <br>
- [BaseStateObject](https://github.com/LCU97/Cat/blob/main/Source/HumanAndCat/Public/Objects/BaseStateObject.h) 에서 [AbilityManagerComponent](https://github.com/LCU97/Cat/blob/main/Source/HumanAndCat/Private/Components/BaseAbilityManagerComponent.cpp) 으로부터 특정 Ability 사용 체크 및 Ability 공통 메서드 실행 <br>

### 3. WeaponComponent <br>

<img width="1157" height="357" alt="image" src="https://github.com/user-attachments/assets/ae79fea6-b354-497a-afb6-cb1beab825da" />

<br>

- [WeaponComponent](https://github.com/LCU97/Cat/blob/8a6c2eae072bd9ccf93ed22a6141b0fd2bd809e6/Source/HumanAndCat/Private/Components/WeaponComponent.cpp#L163) 에서 무기를 장착하면 `StateManagerComponent` 와 `AbilityManagerComponent` 에 무기별로 사용 가능한 State 와 Ability 를 재등록
- [UWeaponProperties](https://github.com/LCU97/Cat/blob/main/Source/HumanAndCat/Public/DataAsset/WeaponProperties.h) 데이터 에셋으로 무기 별로 사용 할 상태와 어빌리티를 에디터에서 설정
<br>

## 🎯 <span style="color:#ff6b6b">Targeting</span>

설계 목표 :
- 타겟 탐색과 전투 상태 관리는 CombatComponent 에서 처리하고 
  카메라 제어는 CameraManagerComponent 에서 담당하도록 설계하여 시스템의 책임을 분리


<img src="https://github.com/user-attachments/assets/51c64be8-c924-40b3-b46c-7c8040c10636" width="450">


### 핵심 코드 <br>

### 1. Combat && Camera <br>
- [CombatComponent](https://github.com/LCU97/Cat/blob/0503f99ac1b10e763ed2d620454a0cf896da3cd7/Source/HumanAndCat/Private/Components/BaseCombatComponent.cpp#L169)에서 타겟 탐색 및 타겟팅 기능 구현
- LockOn 시 부드러운 카메라 움직임 : [CameraManagerComponent](https://github.com/LCU97/Cat/blob/0503f99ac1b10e763ed2d620454a0cf896da3cd7/Source/HumanAndCat/Private/Components/CameraManagerComponent.cpp#L168) 
  
<br>

---

## 개발 기록

- [Character 개발 정리](https://saparation.tistory.com/category/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8/H.W.H)
