package User {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class MineItem extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const MINE_REWARD_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.MineItem.mine_reward_ts", "mineRewardTs", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mineRewardTs:uint;

		/**
		 *  @private
		 */
		public static const MINE_KINGDOM_STATUS:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("User.MineItem.mine_kingdom_status", "mineKingdomStatus", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mineKingdomStatus:Boolean;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mineRewardTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, this.mineKingdomStatus);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var mine_reward_ts$count:uint = 0;
			var mine_kingdom_status$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (mine_reward_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineItem.mineRewardTs cannot be set twice.');
					}
					++mine_reward_ts$count;
					this.mineRewardTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (mine_kingdom_status$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineItem.mineKingdomStatus cannot be set twice.');
					}
					++mine_kingdom_status$count;
					this.mineKingdomStatus = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
