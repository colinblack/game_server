package com.sanguo.game.server.connectlogic.common.message.ProtoChampionship
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class MatchInfoCPP
	{
		public static const PROTO:String = "ProtoChampionship.MatchInfoCPP";
		public var package_root:*;
		public  var message:*;
		public var players:Vector.<MatchUserInfoCPP>;
		public function MatchInfoCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			players = new Vector.<MatchUserInfoCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.players = [];
			for(var i:int = 0;i < this.players.length;i++)
			{
				serializeObj.players.push(this.players[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):MatchInfoCPP
		{
			players = new Vector.<MatchUserInfoCPP>();
			for(var i:int = 0;i < msgObj.players.length;i++)
			{
				this.players.push(new MatchUserInfoCPP(package_root).unserialize(msgObj.players[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MatchInfoCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}