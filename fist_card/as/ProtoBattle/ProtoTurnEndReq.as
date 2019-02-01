package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoTurnEndReq
	{
		public static const PROTO:String = "ProtoBattle.ProtoTurnEndReq";
		public var package_root:*;
		public  var message:*;
		public var battleid:int;
		public var type:int;
		public function ProtoTurnEndReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			battleid = undefined;
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.battleid = this.battleid;
			serializeObj.type = this.type;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoTurnEndReq
		{
			battleid = undefined;
			type = undefined;
			this.battleid = msgObj.battleid;
			this.type = msgObj.type;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoTurnEndReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}