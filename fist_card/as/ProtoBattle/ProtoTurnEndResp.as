package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoTurnEndResp
	{
		public static const PROTO:String = "ProtoBattle.ProtoTurnEndResp";
		public var package_root:*;
		public  var message:*;
		public var nextUser:int;
		public var cards:BattleCardsCPP;
		public var point:int;
		public function ProtoTurnEndResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			nextUser = undefined;
			cards = undefined;
			point = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.nextUser = this.nextUser;
			serializeObj.cards = this.cards.serialize();
			serializeObj.point = this.point;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoTurnEndResp
		{
			nextUser = undefined;
			cards = undefined;
			point = undefined;
			this.nextUser = msgObj.nextUser;
			this.cards = new BattleCardsCPP(package_root).unserialize(msgObj.cards);
			this.point = msgObj.point;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoTurnEndResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}