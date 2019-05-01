package ProtoHero {
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
	public dynamic final class HeroSoldiersCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const HEROID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroSoldiersCPP.heroid", "heroid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var heroid:uint;

		/**
		 *  @private
		 */
		public static const SOLDIERS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroSoldiersCPP.soldiers", "soldiers", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var soldiers:uint;

		/**
		 *  @private
		 */
		public static const MAX:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroSoldiersCPP.max", "max", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var max:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.heroid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.soldiers);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.max);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var heroid$count:uint = 0;
			var soldiers$count:uint = 0;
			var max$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (heroid$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroSoldiersCPP.heroid cannot be set twice.');
					}
					++heroid$count;
					this.heroid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (soldiers$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroSoldiersCPP.soldiers cannot be set twice.');
					}
					++soldiers$count;
					this.soldiers = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (max$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroSoldiersCPP.max cannot be set twice.');
					}
					++max$count;
					this.max = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
