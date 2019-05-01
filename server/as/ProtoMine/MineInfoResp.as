package ProtoMine {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoMine.MineItem;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class MineInfoResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const MINE_EXP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineInfoResp.mine_exp", "mineExp", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mineExp:uint;

		/**
		 *  @private
		 */
		public static const MINE_LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineInfoResp.mine_level", "mineLevel", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mineLevel:uint;

		/**
		 *  @private
		 */
		public static const KINGDOM_MINE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoMine.MineInfoResp.kingdom_mine", "kingdomMine", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoMine.MineItem; });

		public var kingdomMine:ProtoMine.MineItem;

		/**
		 *  @private
		 */
		public static const NORMAL_MINE:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoMine.MineInfoResp.normal_mine", "normalMine", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoMine.MineItem; });

		[ArrayElementType("ProtoMine.MineItem")]
		public var normalMine:Array = [];

		/**
		 *  @private
		 */
		public static const MINE_NORMAL_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineInfoResp.mine_normal_ts", "mineNormalTs", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mineNormalTs:uint;

		/**
		 *  @private
		 */
		public static const MINE_REWARD_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineInfoResp.mine_reward_ts", "mineRewardTs", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mineRewardTs:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mineExp);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mineLevel);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.kingdomMine);
			for (var normalMine$index:uint = 0; normalMine$index < this.normalMine.length; ++normalMine$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.normalMine[normalMine$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mineNormalTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mineRewardTs);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var mine_exp$count:uint = 0;
			var mine_level$count:uint = 0;
			var kingdom_mine$count:uint = 0;
			var mine_normal_ts$count:uint = 0;
			var mine_reward_ts$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (mine_exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineInfoResp.mineExp cannot be set twice.');
					}
					++mine_exp$count;
					this.mineExp = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (mine_level$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineInfoResp.mineLevel cannot be set twice.');
					}
					++mine_level$count;
					this.mineLevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (kingdom_mine$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineInfoResp.kingdomMine cannot be set twice.');
					}
					++kingdom_mine$count;
					this.kingdomMine = new ProtoMine.MineItem();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.kingdomMine);
					break;
				case 4:
					this.normalMine.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoMine.MineItem()));
					break;
				case 5:
					if (mine_normal_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineInfoResp.mineNormalTs cannot be set twice.');
					}
					++mine_normal_ts$count;
					this.mineNormalTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (mine_reward_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineInfoResp.mineRewardTs cannot be set twice.');
					}
					++mine_reward_ts$count;
					this.mineRewardTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
