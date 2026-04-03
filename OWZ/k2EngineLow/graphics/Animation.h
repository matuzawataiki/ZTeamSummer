/*!
* @brief	�A�j���[�V����
*/

#pragma once

#include "AnimationClip.h"
#include "AnimationPlayController.h"


namespace nsK2EngineLow {
	struct AnimationData
	{
		const char* filePath;
		bool loopFlag;

		AnimationData(const char* f, bool l) :filePath(f), loopFlag(l) {}
	};

	class Skeleton;
	using AnimationEventListener = std::function<void(const wchar_t* clipName, const wchar_t* eventName)>;

	/// <summary>
	/// �A�j���[�V�����N���X�B
	/// </summary>
	/// <remarks>
	/// �񋟂���@�\
	/// �P. �V���v���ȃA�j���[�V�����Đ��B
	/// �Q. �A�j���[�V������ԁB
	/// �R. footstep�{�[�������p�����A�j���[�V�����ړ��ʂ̌v�Z�B
	///		�X�P���g����footstep�{�[����ǉ�����ƁA�S�̂̃{�[������A
	///		footstep�{�[���̕��s�ړ��ʂ����O�����A�j���[�V�����Đ����s���܂��B
	///		���O���ꂽ�ړ��ʂ�CalcFootstepDeltaValueInWorldSpace�֐��𗘗p���邱�Ƃ�
	///		�v�Z���邱�Ƃ��ł��܂��B
	///		���̋@�\�����p���邱�ƂŁA�A�j���[�^���쐬���������A�j���[�V�����ȂǂɈړ��ʂ�
	///		�܂ނ��Ƃ��ł��A�A�j���[�^���Ӑ}�����ړ����s�����Ƃ��ł��܂��B
	/// </remarks>
	class Animation : public Noncopyable {
	public:
		
		/// <summary>
		/// �������ς݂�����B
		/// </summary>
		/// <returns>true���Ԃ��Ă����珉�����ς݁B</returns>
		bool IsInited() const
		{
			return m_isInited;
		}

		/// <summary>
		/// �������B
		/// </summary>
		/// <param name="skeleton">�A�j���[�V����������X�P���g��</param>
		/// <param name="animClips">�A�j���[�V�����N���b�v�̔z��</param>
		/// <param name="numAnimClip">�A�j���[�V�����N���b�v�̐�</param>
		void Init(
			Skeleton& skeleton,
			AnimationClip* animClips,
			int numAnimClip
		);
		/// <summary>
		/// �A�j���[�V�����̍Đ��B
		/// </summary>
		/// <param name="clipNo">�A�j���[�V�����N���b�v�̔ԍ��BInit�֐��ɓn����animClipList�̕��тƂȂ�B</param>
		/// <param name="interpolateTime">�⊮����(�P�ʁF�b)</param>
		void Play(int clipNo, float interpolateTime = 0.0f)
		{
			if (clipNo < m_animationClips.size()) {
				PlayCommon(m_animationClips[clipNo], interpolateTime);
			}
		}
		/// <summary>
		/// �A�j���[�V�����N���b�v�̃��[�v�t���O��ݒ肵�܂��B
		/// </summary>
		/// <param name="clipName">�A�j���[�V�����N���b�v�̖��O</param>
		/// <param name="flag">�t���O</param>
		void SetAnimationClipLoopFlag(const wchar_t* clipName, bool flag)
		{
			auto it = std::find_if(
				m_animationClips.begin(),
				m_animationClips.end(),
				[clipName](auto& clip) {return clip->GetName() == clipName; }
			);
			if (it == m_animationClips.end()) {
				//������Ȃ������B
				return;
			}
			(*it)->SetLoopFlag(flag);
		}
		/// <summary>
		/// �A�j���[�V�����̍Đ����H
		/// </summary>
		/// <returns></returns>
		bool IsPlaying() const
		{
			int lastIndex = GetLastAnimationControllerIndex();
			return m_animationPlayController[lastIndex].IsPlaying();
		}

		/// <summary>
		/// �A�j���[�V������i�߂�B
		/// </summary>
		/// <remarks>
		/// �G���W����������Ă΂�܂��B
		/// ���[�U�[�͎g�p���Ȃ��ł��������B
		/// </remarks>
		/// <param name="deltaTime">�A�j���[�V������i�߂鎞��(�P�ʁF�b)</param>
		void Progress(float deltaTime);
		/*!
		*@brief	�A�j���[�V�����C�x���g���X�i�[��o�^�B
		*@return
		* �o�^���ꂽ���X�i�[�B
		*/
		
		/// <summary>
		/// �A�j���[�V�����C�x���g���X�i�[��o�^�B
		/// </summary>
		/// <param name="eventListener">�o�^���郊�X�i�[�B</param>
		void AddAnimationEventListener(AnimationEventListener eventListener)
		{
			m_animationEventListeners.push_back(eventListener);
		}

		/// <summary>
		/// �A�j���[�V�����C�x���g�����X�i�[�ɒʒm�B
		/// </summary>
		/// <param name="clipName">�C�x���g���N�������A�j���[�V�����N���b�v�̖��O</param>
		/// <param name="eventName">�C�x���g���B</param>
		void NotifyAnimationEventToListener(const wchar_t* clipName, const wchar_t* eventName)
		{
			for (auto& listener : m_animationEventListeners) {
				listener(clipName, eventName);
			}
		}
		/// <summary>
		/// ���[���h��Ԃł̃t�b�g�X�e�b�v�̈ړ��ʂ��v�Z����B
		/// </summary>
		/// <remarks>
		/// �t�b�g�X�e�b�v�̈ړ��ʂ́A���f���̃��[�g����̑��Έړ��ʂł��B
		/// ���̂��߁A���[���h��Ԃɕϊ�����̂ɕ��s�ړ��ʂ͕s�v�ł��B
		/// ���f���̉�]�N�H�[�^�j�I���Ɗg�嗦�̂ݎw�肵�Ă��������B
		/// </remarks>
		/// <param name="rotation">���f���̉�]</param>
		/// <param name="scale">���f���̊g�嗦</param>
		/// <returns>���[���h��Ԃł̃t�b�g�X�e�b�v�̈ړ��ʁB</returns>
		Vector3 CalcFootstepDeltaValueInWorldSpace(Quaternion rotation, Vector3 scale) const;

	private:
		void PlayCommon(AnimationClip* nextClip, float interpolateTime)
		{
			int index = GetLastAnimationControllerIndex();
			if (m_animationPlayController[index].GetAnimClip() == nextClip) {
				return;
			}
			if (interpolateTime == 0.0f) {
				//�⊮�Ȃ��B
				m_numAnimationPlayController = 1;
			}
			else {
				//�⊮����B
				m_numAnimationPlayController++;
			}
			index = GetLastAnimationControllerIndex();
			m_animationPlayController[index].ChangeAnimationClip(nextClip);
			m_animationPlayController[index].SetInterpolateTime(interpolateTime);
			m_interpolateTime = 0.0f;
			m_interpolateTimeEnd = interpolateTime;
		}
		/// <summary>
		/// ���[�J���|�[�Y�̍X�V�B
		/// </summary>
		/// <param name="deltaTime">�A�j���[�V������i�߂鎞�ԁB�P�ʁF�b�B</param>
		void UpdateLocalPose(float deltaTime);
		/// <summary>
		/// �O���[�o���|�[�Y�̍X�V�B
		/// </summary>
		void UpdateGlobalPose();
	private:

		/// <summary>
		/// �ŏI�|�[�Y�ɂȂ�A�j���[�V�����̃����O�o�b�t�@��ł̃C���f�b�N�X���擾�B
		/// </summary>
		/// <returns></returns>
		int GetLastAnimationControllerIndex() const
		{
			return GetAnimationControllerIndex(m_startAnimationPlayController, m_numAnimationPlayController - 1);
		}
		/// <summary>
		/// �A�j���[�V�����R���g���[���[�̃����O�o�b�t�@��ł̃C���f�b�N�X���擾
		/// </summary>
		/// <param name="startIndex">�J�n�C���f�b�N�X</param>
		/// <param name="localIndex">���[�J���C���f�b�N�X</param>
		/// <returns></returns>
		int GetAnimationControllerIndex(int startIndex, int localIndex) const
		{
			return (startIndex + localIndex) % ANIMATION_PLAY_CONTROLLER_NUM;
		}

	private:
		static const int ANIMATION_PLAY_CONTROLLER_NUM = 32;	//!<�A�j���[�V�����R���g���[���̐��B
		std::vector<AnimationClip*>	m_animationClips;	//!<�A�j���[�V�����N���b�v�̔z��B
		Skeleton* m_skeleton = nullptr;	//!<�A�j���[�V������K�p����X�P���g���B
		AnimationPlayController	m_animationPlayController[ANIMATION_PLAY_CONTROLLER_NUM];	//!<�A�j���[�V�����R���g���[���B�����O�o�b�t�@�B
		int m_numAnimationPlayController = 0;		//!<���ݎg�p���̃A�j���[�V�����Đ��R���g���[���̐��B
		int m_startAnimationPlayController = 0;		//!<�A�j���[�V�����R���g���[���̊J�n�C���f�b�N�X�B
		float m_interpolateTime = 0.0f;
		float m_interpolateTimeEnd = 0.0f;
		bool m_isInterpolate = false;								//!<��Ԓ��H
		std::vector<AnimationEventListener>	m_animationEventListeners;	//!<�A�j���[�V�����C�x���g���X�i�[�̃��X�g�B
		Vector3 m_footstepDeltaValue = g_vec3Zero;					//footstep�{�[���̈ړ��ʁB
		bool m_isInited = false;
		float m_deltaTimeOnUpdate = 0.0f;							//Update�֐������s�����Ƃ��̃f���^�^�C���B
	};
}