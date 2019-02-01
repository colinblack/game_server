package com.sanguo.game.server.connectlogic.common.message.ProtoBattleBase
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleReq
	{
		public static const PROTO:String = "ProtoBattleBase.ProtoBattleReq";
		public var package_root:*;
		public  var message:*;
		public var battleid:int;
		public var type:int;
		public var ud:int;
		public var cardid:int;
		public var heroid:int;
		public function ProtoBattleReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			battleid = undefined;
			type = undefined;
			ud = undefined;
			cardid = undefined;
			heroid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.battleid = this.battleid;
			serializeObj.type = this.type;
			serializeObj.ud = this.ud;
			serializeObj.cardid = this.cardid;
			serializeObj.heroid = this.heroid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleReq
		{
			battleid = undefined;
			type = undefined;
			ud = undefined;
			cardid = undefined;
			heroid = undefined;
			this.battleid = msgObj.battleid;
			this.type = msgObj.type;
			this.ud = msgObj.ud;
			this.cardid = msgObj.cardid;
			this.heroid = msgObj.heroid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}