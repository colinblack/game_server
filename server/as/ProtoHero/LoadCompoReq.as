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
	public dynamic final class LoadCompoReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const HEROID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.LoadCompoReq.heroid", "heroid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var heroid:uint;

		/**
		 *  @private
		 */
		public static const COMPUD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.LoadCompoReq.compud", "compud", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var compud:uint;

		/**
		 *  @private
		 */
		public static const POS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.LoadCompoReq.pos", "pos", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var pos:uint;

		/**
		 *  @private
		 */
		public static const OLDCOMPUD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.LoadCompoReq.oldcompud", "oldcompud", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		private var oldcompud$field:uint;

		private var hasField$0:uint = 0;

		public function clearOldcompud():void {
			hasField$0 &= 0xfffffffe;
			oldcompud$field = new uint();
		}

		public function get hasOldcompud():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set oldcompud(value:uint):void {
			hasField$0 |= 0x1;
			oldcompud$field = value;
		}

		public function get oldcompud():uint {
			return oldcompud$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.heroid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.compud);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.pos);
			if (hasOldcompud) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, oldcompud$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var heroid$count:uint = 0;
			var compud$count:uint = 0;
			var pos$count:uint = 0;
			var oldcompud$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (heroid$count != 0) {
						throw new flash.errors.IOError('Bad data format: LoadCompoReq.heroid cannot be set twice.');
					}
					++heroid$count;
					this.heroid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (compud$count != 0) {
						throw new flash.errors.IOError('Bad data format: LoadCompoReq.compud cannot be set twice.');
					}
					++compud$count;
					this.compud = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (pos$count != 0) {
						throw new flash.errors.IOError('Bad data format: LoadCompoReq.pos cannot be set twice.');
					}
					++pos$count;
					this.pos = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (oldcompud$count != 0) {
						throw new flash.errors.IOError('Bad data format: LoadCompoReq.oldcompud cannot be set twice.');
					}
					++oldcompud$count;
					this.oldcompud = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
