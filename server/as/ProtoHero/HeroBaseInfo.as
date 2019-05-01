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
	public dynamic final class HeroBaseInfo extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const HEROID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfo.heroid", "heroid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var heroid:uint;

		/**
		 *  @private
		 */
		public static const STATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfo.status", "status", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var status:uint;

		/**
		 *  @private
		 */
		public static const LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfo.level", "level", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var level:uint;

		/**
		 *  @private
		 */
		public static const EXP:FieldDescriptor_TYPE_UINT64 = new FieldDescriptor_TYPE_UINT64("ProtoHero.HeroBaseInfo.exp", "exp", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var exp:UInt64;

		/**
		 *  @private
		 */
		public static const ATTACKNUM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfo.attacknum", "attacknum", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var attacknum:uint;

		/**
		 *  @private
		 */
		public static const OVONUM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfo.ovonum", "ovonum", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ovonum:uint;

		/**
		 *  @private
		 */
		public static const KILLNUM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfo.killnum", "killnum", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var killnum:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.heroid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.status);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.level);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT64(output, this.exp);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.attacknum);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ovonum);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.killnum);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var heroid$count:uint = 0;
			var status$count:uint = 0;
			var level$count:uint = 0;
			var exp$count:uint = 0;
			var attacknum$count:uint = 0;
			var ovonum$count:uint = 0;
			var killnum$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (heroid$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfo.heroid cannot be set twice.');
					}
					++heroid$count;
					this.heroid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (status$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfo.status cannot be set twice.');
					}
					++status$count;
					this.status = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (level$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfo.level cannot be set twice.');
					}
					++level$count;
					this.level = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfo.exp cannot be set twice.');
					}
					++exp$count;
					this.exp = com.netease.protobuf.ReadUtils.read_TYPE_UINT64(input);
					break;
				case 5:
					if (attacknum$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfo.attacknum cannot be set twice.');
					}
					++attacknum$count;
					this.attacknum = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (ovonum$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfo.ovonum cannot be set twice.');
					}
					++ovonum$count;
					this.ovonum = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (killnum$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfo.killnum cannot be set twice.');
					}
					++killnum$count;
					this.killnum = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
