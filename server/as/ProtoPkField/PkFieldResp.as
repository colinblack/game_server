package ProtoPkField {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoPkField.PkUserItem;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class PkFieldResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const RANK:FieldDescriptor_TYPE_INT32 = new FieldDescriptor_TYPE_INT32("ProtoPkField.PkFieldResp.rank", "rank", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var rank:int;

		/**
		 *  @private
		 */
		public static const CHALLENGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoPkField.PkFieldResp.challenge", "challenge", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var challenge:uint;

		/**
		 *  @private
		 */
		public static const WINNERS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoPkField.PkFieldResp.winners", "winners", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoPkField.PkUserItem; });

		[ArrayElementType("ProtoPkField.PkUserItem")]
		public var winners:Array = [];

		/**
		 *  @private
		 */
		public static const DEFIER:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoPkField.PkFieldResp.defier", "defier", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoPkField.PkUserItem; });

		[ArrayElementType("ProtoPkField.PkUserItem")]
		public var defier:Array = [];

		/**
		 *  @private
		 */
		public static const REWARD_RANK:FieldDescriptor_TYPE_INT32 = new FieldDescriptor_TYPE_INT32("ProtoPkField.PkFieldResp.reward_rank", "rewardRank", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var rewardRank:int;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_INT32(output, this.rank);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.challenge);
			for (var winners$index:uint = 0; winners$index < this.winners.length; ++winners$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.winners[winners$index]);
			}
			for (var defier$index:uint = 0; defier$index < this.defier.length; ++defier$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.defier[defier$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_INT32(output, this.rewardRank);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var rank$count:uint = 0;
			var challenge$count:uint = 0;
			var reward_rank$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (rank$count != 0) {
						throw new flash.errors.IOError('Bad data format: PkFieldResp.rank cannot be set twice.');
					}
					++rank$count;
					this.rank = com.netease.protobuf.ReadUtils.read_TYPE_INT32(input);
					break;
				case 2:
					if (challenge$count != 0) {
						throw new flash.errors.IOError('Bad data format: PkFieldResp.challenge cannot be set twice.');
					}
					++challenge$count;
					this.challenge = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					this.winners.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoPkField.PkUserItem()));
					break;
				case 4:
					this.defier.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoPkField.PkUserItem()));
					break;
				case 5:
					if (reward_rank$count != 0) {
						throw new flash.errors.IOError('Bad data format: PkFieldResp.rewardRank cannot be set twice.');
					}
					++reward_rank$count;
					this.rewardRank = com.netease.protobuf.ReadUtils.read_TYPE_INT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
