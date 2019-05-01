package ProtoMission {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoMission.MissionAllCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class GetMissionRewardResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const FOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMission.GetMissionRewardResp.food", "food", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var food:uint;

		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMission.GetMissionRewardResp.coin", "coin", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var coin:uint;

		/**
		 *  @private
		 */
		public static const WOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMission.GetMissionRewardResp.wood", "wood", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var wood:uint;

		/**
		 *  @private
		 */
		public static const EXP:FieldDescriptor_TYPE_UINT64 = new FieldDescriptor_TYPE_UINT64("ProtoMission.GetMissionRewardResp.exp", "exp", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var exp:UInt64;

		/**
		 *  @private
		 */
		public static const LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMission.GetMissionRewardResp.level", "level", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var level:uint;

		/**
		 *  @private
		 */
		public static const NEXTMISSION:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoMission.GetMissionRewardResp.nextmission", "nextmission", (6 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoMission.MissionAllCPP; });

		public var nextmission:ProtoMission.MissionAllCPP;

		/**
		 *  @private
		 */
		public static const HAMMER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMission.GetMissionRewardResp.hammer", "hammer", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		private var hammer$field:uint;

		private var hasField$0:uint = 0;

		public function clearHammer():void {
			hasField$0 &= 0xfffffffe;
			hammer$field = new uint();
		}

		public function get hasHammer():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set hammer(value:uint):void {
			hasField$0 |= 0x1;
			hammer$field = value;
		}

		public function get hammer():uint {
			return hammer$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.food);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.coin);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.wood);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT64(output, this.exp);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.level);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.nextmission);
			if (hasHammer) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, hammer$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var food$count:uint = 0;
			var coin$count:uint = 0;
			var wood$count:uint = 0;
			var exp$count:uint = 0;
			var level$count:uint = 0;
			var nextmission$count:uint = 0;
			var hammer$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (food$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetMissionRewardResp.food cannot be set twice.');
					}
					++food$count;
					this.food = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetMissionRewardResp.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (wood$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetMissionRewardResp.wood cannot be set twice.');
					}
					++wood$count;
					this.wood = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetMissionRewardResp.exp cannot be set twice.');
					}
					++exp$count;
					this.exp = com.netease.protobuf.ReadUtils.read_TYPE_UINT64(input);
					break;
				case 5:
					if (level$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetMissionRewardResp.level cannot be set twice.');
					}
					++level$count;
					this.level = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (nextmission$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetMissionRewardResp.nextmission cannot be set twice.');
					}
					++nextmission$count;
					this.nextmission = new ProtoMission.MissionAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.nextmission);
					break;
				case 7:
					if (hammer$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetMissionRewardResp.hammer cannot be set twice.');
					}
					++hammer$count;
					this.hammer = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
