package ProtoModelTrial {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoModelTrial.ModelTrialCPP;
	import User.RewardBagInfo;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class PushTrialRewardReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ISFIRST:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("ProtoModelTrial.PushTrialRewardReq.isfirst", "isfirst", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var isfirst:Boolean;

		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoModelTrial.PushTrialRewardReq.reward", "reward", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.RewardBagInfo; });

		public var reward:User.RewardBagInfo;

		/**
		 *  @private
		 */
		public static const MODELTRIAL:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoModelTrial.PushTrialRewardReq.modeltrial", "modeltrial", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoModelTrial.ModelTrialCPP; });

		private var modeltrial$field:ProtoModelTrial.ModelTrialCPP;

		public function clearModeltrial():void {
			modeltrial$field = null;
		}

		public function get hasModeltrial():Boolean {
			return modeltrial$field != null;
		}

		public function set modeltrial(value:ProtoModelTrial.ModelTrialCPP):void {
			modeltrial$field = value;
		}

		public function get modeltrial():ProtoModelTrial.ModelTrialCPP {
			return modeltrial$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, this.isfirst);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.reward);
			if (hasModeltrial) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, modeltrial$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var isfirst$count:uint = 0;
			var reward$count:uint = 0;
			var modeltrial$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (isfirst$count != 0) {
						throw new flash.errors.IOError('Bad data format: PushTrialRewardReq.isfirst cannot be set twice.');
					}
					++isfirst$count;
					this.isfirst = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				case 2:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: PushTrialRewardReq.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = new User.RewardBagInfo();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.reward);
					break;
				case 3:
					if (modeltrial$count != 0) {
						throw new flash.errors.IOError('Bad data format: PushTrialRewardReq.modeltrial cannot be set twice.');
					}
					++modeltrial$count;
					this.modeltrial = new ProtoModelTrial.ModelTrialCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.modeltrial);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
