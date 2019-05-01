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
	public dynamic final class HeroBaseInfoCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const HEROID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfoCPP.heroid", "heroid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var heroid:uint;

		/**
		 *  @private
		 */
		public static const STATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfoCPP.status", "status", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var status:uint;

		/**
		 *  @private
		 */
		public static const LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfoCPP.level", "level", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var level:uint;

		/**
		 *  @private
		 */
		public static const EXP:FieldDescriptor_TYPE_UINT64 = new FieldDescriptor_TYPE_UINT64("ProtoHero.HeroBaseInfoCPP.exp", "exp", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var exp:UInt64;

		/**
		 *  @private
		 */
		public static const ATTACKNUM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfoCPP.attacknum", "attacknum", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var attacknum:uint;

		/**
		 *  @private
		 */
		public static const OVONUM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfoCPP.ovonum", "ovonum", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ovonum:uint;

		/**
		 *  @private
		 */
		public static const KILLNUM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfoCPP.killnum", "killnum", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var killnum:uint;

		/**
		 *  @private
		 */
		public static const HP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfoCPP.hp", "hp", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		public var hp:uint;

		/**
		 *  @private
		 */
		public static const ATTACK:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfoCPP.attack", "attack", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		public var attack:uint;

		/**
		 *  @private
		 */
		public static const DEFEND:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfoCPP.defend", "defend", (10 << 3) | com.netease.protobuf.WireType.VARINT);

		public var defend:uint;

		/**
		 *  @private
		 */
		public static const RULE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfoCPP.rule", "rule", (11 << 3) | com.netease.protobuf.WireType.VARINT);

		public var rule:uint;

		/**
		 *  @private
		 */
		public static const COURAGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfoCPP.courage", "courage", (12 << 3) | com.netease.protobuf.WireType.VARINT);

		public var courage:uint;

		/**
		 *  @private
		 */
		public static const POWER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.HeroBaseInfoCPP.power", "power", (13 << 3) | com.netease.protobuf.WireType.VARINT);

		private var power$field:uint;

		private var hasField$0:uint = 0;

		public function clearPower():void {
			hasField$0 &= 0xfffffffe;
			power$field = new uint();
		}

		public function get hasPower():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set power(value:uint):void {
			hasField$0 |= 0x1;
			power$field = value;
		}

		public function get power():uint {
			return power$field;
		}

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
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.hp);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.attack);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 10);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.defend);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 11);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.rule);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 12);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.courage);
			if (hasPower) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 13);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, power$field);
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
			var status$count:uint = 0;
			var level$count:uint = 0;
			var exp$count:uint = 0;
			var attacknum$count:uint = 0;
			var ovonum$count:uint = 0;
			var killnum$count:uint = 0;
			var hp$count:uint = 0;
			var attack$count:uint = 0;
			var defend$count:uint = 0;
			var rule$count:uint = 0;
			var courage$count:uint = 0;
			var power$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (heroid$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.heroid cannot be set twice.');
					}
					++heroid$count;
					this.heroid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (status$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.status cannot be set twice.');
					}
					++status$count;
					this.status = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (level$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.level cannot be set twice.');
					}
					++level$count;
					this.level = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.exp cannot be set twice.');
					}
					++exp$count;
					this.exp = com.netease.protobuf.ReadUtils.read_TYPE_UINT64(input);
					break;
				case 5:
					if (attacknum$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.attacknum cannot be set twice.');
					}
					++attacknum$count;
					this.attacknum = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (ovonum$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.ovonum cannot be set twice.');
					}
					++ovonum$count;
					this.ovonum = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (killnum$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.killnum cannot be set twice.');
					}
					++killnum$count;
					this.killnum = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (hp$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.hp cannot be set twice.');
					}
					++hp$count;
					this.hp = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 9:
					if (attack$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.attack cannot be set twice.');
					}
					++attack$count;
					this.attack = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 10:
					if (defend$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.defend cannot be set twice.');
					}
					++defend$count;
					this.defend = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 11:
					if (rule$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.rule cannot be set twice.');
					}
					++rule$count;
					this.rule = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 12:
					if (courage$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.courage cannot be set twice.');
					}
					++courage$count;
					this.courage = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 13:
					if (power$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroBaseInfoCPP.power cannot be set twice.');
					}
					++power$count;
					this.power = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
