package ProtoBuilding {
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
	public dynamic final class BuildUserSyncInfo extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const TOTAL_EXPLOIT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBuilding.BuildUserSyncInfo.total_exploit", "totalExploit", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var totalExploit:uint;

		/**
		 *  @private
		 */
		public static const USER_COINS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBuilding.BuildUserSyncInfo.user_coins", "userCoins", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var userCoins:uint;

		/**
		 *  @private
		 */
		public static const USER_WOODS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBuilding.BuildUserSyncInfo.user_woods", "userWoods", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var userWoods:uint;

		/**
		 *  @private
		 */
		public static const USER_EXP:FieldDescriptor_TYPE_UINT64 = new FieldDescriptor_TYPE_UINT64("ProtoBuilding.BuildUserSyncInfo.user_exp", "userExp", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var userExp:UInt64;

		/**
		 *  @private
		 */
		public static const USER_LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBuilding.BuildUserSyncInfo.user_level", "userLevel", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var userLevel:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.totalExploit);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.userCoins);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.userWoods);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT64(output, this.userExp);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.userLevel);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var total_exploit$count:uint = 0;
			var user_coins$count:uint = 0;
			var user_woods$count:uint = 0;
			var user_exp$count:uint = 0;
			var user_level$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (total_exploit$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuildUserSyncInfo.totalExploit cannot be set twice.');
					}
					++total_exploit$count;
					this.totalExploit = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (user_coins$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuildUserSyncInfo.userCoins cannot be set twice.');
					}
					++user_coins$count;
					this.userCoins = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (user_woods$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuildUserSyncInfo.userWoods cannot be set twice.');
					}
					++user_woods$count;
					this.userWoods = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (user_exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuildUserSyncInfo.userExp cannot be set twice.');
					}
					++user_exp$count;
					this.userExp = com.netease.protobuf.ReadUtils.read_TYPE_UINT64(input);
					break;
				case 5:
					if (user_level$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuildUserSyncInfo.userLevel cannot be set twice.');
					}
					++user_level$count;
					this.userLevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
