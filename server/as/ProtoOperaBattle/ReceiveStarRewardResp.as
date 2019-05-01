package ProtoOperaBattle {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoOperaBattle.OperaBattleCPP;
	import User.RewardBagInfo;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ReceiveStarRewardResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOperaBattle.ReceiveStarRewardResp.cash", "cash", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cash:uint;

		/**
		 *  @private
		 */
		public static const OPERABATTLE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoOperaBattle.ReceiveStarRewardResp.operabattle", "operabattle", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoOperaBattle.OperaBattleCPP; });

		public var operabattle:ProtoOperaBattle.OperaBattleCPP;

		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoOperaBattle.ReceiveStarRewardResp.reward", "reward", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.RewardBagInfo; });

		public var reward:User.RewardBagInfo;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cash);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.operabattle);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.reward);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var cash$count:uint = 0;
			var operabattle$count:uint = 0;
			var reward$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReceiveStarRewardResp.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (operabattle$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReceiveStarRewardResp.operabattle cannot be set twice.');
					}
					++operabattle$count;
					this.operabattle = new ProtoOperaBattle.OperaBattleCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.operabattle);
					break;
				case 3:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReceiveStarRewardResp.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = new User.RewardBagInfo();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.reward);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
