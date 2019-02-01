package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class MartialClubGroup
	{
		public static const PROTO:String = "ProtoMartialClub.MartialClubGroup";
		public var package_root:*;
		public  var message:*;
		public var clubs:Vector.<SingleMartialClub>;
		public function MartialClubGroup(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			clubs = new Vector.<SingleMartialClub>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.clubs = [];
			for(var i:int = 0;i < this.clubs.length;i++)
			{
				serializeObj.clubs.push(this.clubs[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):MartialClubGroup
		{
			clubs = new Vector.<SingleMartialClub>();
			for(var i:int = 0;i < msgObj.clubs.length;i++)
			{
				this.clubs.push(new SingleMartialClub(package_root).unserialize(msgObj.clubs[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MartialClubGroup
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}