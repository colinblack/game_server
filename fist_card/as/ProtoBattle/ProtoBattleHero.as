package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleHero
	{
		public static const PROTO:String = "ProtoBattle.ProtoBattleHero";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var hp:int;
		public var att:int;
		public var def:int;
		public var shield:int;
		public var battlePower:int;
		public var damInc:Number;
		public var damDec:Number;
		public function ProtoBattleHero(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			id = undefined;
			hp = undefined;
			att = undefined;
			def = undefined;
			shield = undefined;
			battlePower = undefined;
			damInc = undefined;
			damDec = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.hp = this.hp;
			serializeObj.att = this.att;
			serializeObj.def = this.def;
			serializeObj.shield = this.shield;
			serializeObj.battlePower = this.battlePower;
			serializeObj.damInc = this.damInc;
			serializeObj.damDec = this.damDec;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleHero
		{
			id = undefined;
			hp = undefined;
			att = undefined;
			def = undefined;
			shield = undefined;
			battlePower = undefined;
			damInc = undefined;
			damDec = undefined;
			this.id = msgObj.id;
			this.hp = msgObj.hp;
			this.att = msgObj.att;
			this.def = msgObj.def;
			this.shield = msgObj.shield;
			this.battlePower = msgObj.battlePower;
			this.damInc = msgObj.damInc;
			this.damDec = msgObj.damDec;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleHero
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}