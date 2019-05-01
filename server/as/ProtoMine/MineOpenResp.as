package ProtoMine {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.UserResourceCPP;
	import ProtoMine.MineItem;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class MineOpenResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const MINE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoMine.MineOpenResp.mine", "mine", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoMine.MineItem; });

		public var mine:ProtoMine.MineItem;

		/**
		 *  @private
		 */
		public static const ASSETS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoMine.MineOpenResp.assets", "assets", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.UserResourceCPP; });

		public var assets:DataCommon.UserResourceCPP;

		/**
		 *  @private
		 */
		public static const MINE_EXP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineOpenResp.mine_exp", "mineExp", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mineExp:uint;

		/**
		 *  @private
		 */
		public static const MINE_LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineOpenResp.mine_level", "mineLevel", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mineLevel:uint;

		/**
		 *  @private
		 */
		public static const MINE_NORMAL_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineOpenResp.mine_normal_ts", "mineNormalTs", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		private var mine_normal_ts$field:uint;

		private var hasField$0:uint = 0;

		public function clearMineNormalTs():void {
			hasField$0 &= 0xfffffffe;
			mine_normal_ts$field = new uint();
		}

		public function get hasMineNormalTs():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set mineNormalTs(value:uint):void {
			hasField$0 |= 0x1;
			mine_normal_ts$field = value;
		}

		public function get mineNormalTs():uint {
			return mine_normal_ts$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.mine);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.assets);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mineExp);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mineLevel);
			if (hasMineNormalTs) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, mine_normal_ts$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var mine$count:uint = 0;
			var assets$count:uint = 0;
			var mine_exp$count:uint = 0;
			var mine_level$count:uint = 0;
			var mine_normal_ts$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (mine$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineOpenResp.mine cannot be set twice.');
					}
					++mine$count;
					this.mine = new ProtoMine.MineItem();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.mine);
					break;
				case 2:
					if (assets$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineOpenResp.assets cannot be set twice.');
					}
					++assets$count;
					this.assets = new DataCommon.UserResourceCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.assets);
					break;
				case 3:
					if (mine_exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineOpenResp.mineExp cannot be set twice.');
					}
					++mine_exp$count;
					this.mineExp = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (mine_level$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineOpenResp.mineLevel cannot be set twice.');
					}
					++mine_level$count;
					this.mineLevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (mine_normal_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineOpenResp.mineNormalTs cannot be set twice.');
					}
					++mine_normal_ts$count;
					this.mineNormalTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
